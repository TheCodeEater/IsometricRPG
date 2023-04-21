#include "../../../include/gameInterface/widgets/widgets.hpp"

#include <iostream>
#include <stdexcept>

#include "../../../include/gameInterface/gameInterface.hpp"

namespace IsoRPG {
// class BaseWidget

// constructor
BaseWidget::BaseWidget(W& window, short z_index)
    : w_{WindowWrapper{window}}, zIndex_{z_index} {}

// nested class for window wrapping
BaseWidget::WindowWrapper::WindowWrapper(W& window) : w_{window} {}

void BaseWidget::WindowWrapper::draw(const sf::Drawable& drawable) const {
  w_.draw(drawable);
}

// event dispatcher
void BaseWidget::onEvent(sf::Event const& e) {
  // swith between the possible event types
  switch (e.type) {
    case sf::Event::MouseButtonReleased:
      onClick(e);
      break;
    case sf::Event::KeyPressed:
      onKeyPressed(e);
      break;
    case sf::Event::MouseMoved:
      onMouseMove(e);
      break;
  }
}

// event handlers
void BaseWidget::onClick(sf::Event const& e) {}
void BaseWidget::onMouseMove(sf::Event const& e) {}
void BaseWidget::onKeyPressed(sf::Event const& e) {}

// z-indexing
void BaseWidget::setZIndex(short val) { zIndex_ = val; }

short BaseWidget::getZIndex() const { return zIndex_; }

// window access
BaseWidget::WindowWrapper const& BaseWidget::getWindow() const { return w_; }

// base widget
// constructor default
template <class graphic_object>
Widget<graphic_object>::Widget(W& window, short z_index)
    : BaseWidget{window, z_index}, graphicObject_{} {}

template <class graphic_object>
Widget<graphic_object>::Widget(W& window, graphic_object&& graphic,
                               short z_index)
    : Widget{window, z_index}, graphicObject_{std::move(graphic)} {}
// construct from pre existing sfml object
template <class graphic_object>
Widget<graphic_object>::Widget(W& window,
                               std::function<void(GraphicWrapper&)> processFunc,
                               short z_index)
    : Widget{window, z_index} {
  // create wrapper
  GraphicWrapper g_wrapper{graphicObject_};
  // apply the function to the wrapper
  processFunc(g_wrapper);
}
//another lambda
template <class graphic_object>
Widget<graphic_object>::Widget(W& window, std::function<graphic_object(void)> processFunc, short z_index)
  : Widget{window, z_index}{
    graphicObject_=processFunc();
  }

// wrapper class for graphic objects manipulation in lambdas
template <class graphic_object>
Widget<graphic_object>::GraphicWrapper::GraphicWrapper(graphic_object& g)
    : gObj_{g} {}  // create reference to the object

template <class graphic_object>
void Widget<graphic_object>::GraphicWrapper::assign(graphic_object&& g) {
  gObj_ = std::move(g);  // move create graphic object
}

template <class graphic_object>
void Widget<graphic_object>::draw() const {
  // draw underlying graphic object
  getWindow().draw(*graphicObject_);
}

template <class graphic_object>
void Widget<graphic_object>::setPosition(sf::Vector2f pos) {
  // call underlying sfml set position
  graphicObject_->setPosition(pos);
}

template <class graphic_object>
sf::Vector2f Widget<graphic_object>::getPosition() const {
  // call sfml get position
  return graphicObject_->getPosition();
}
/*
// CLASS WIDGET
widget::widget(W& window, Z_IND_T zindex) : w_{window}, z_index_{zindex} {}
widget::~widget() = default;

// events
void widget::onClick(sf::Event const&) {}  // default implementation is empty
void widget::setClickHandler(std::function<void(void)>&& h) {
  clickHandler = h;
}
std::function<void(void)> const& widget::getClickHandler() const {
  return clickHandler;
}

// updating
void widget::update() {}

// graphics
void widget::setTextureID(Textures::ID id) { t_id_ = id; }
widget::G_OBJ* widget::getGraphic() const { return graphicObject_.get(); }
void widget::setGraphic(G_OBJ* g) {
  graphicObject_ = std::unique_ptr<G_OBJ>(g);
}

void widget::setGraphic(G_OBJ_PTR&& g) { graphicObject_ = std::move(g); }

W& widget::getWindow() const { return w_; }

void widget::draw() const { w_.draw(*graphicObject_); }

widget::Z_IND_T widget::getZInd() const { return z_index_; }

void widget::setZInd(Z_IND_T value) {
  // set the value
  z_index_ = value;
}

// CLASSE IMAGE

Image::Image(W& window, Z_IND_T z_index = 0)
    : Box(window, z_index) {  // creates empty image - for testing
  setGraphic(new sf::RectangleShape{});
}

Image::Image(W& window, const sf::Texture* t, Z_IND_T z_index)
    : Image(window, t, sf::Vector2f{0, 0},
            sf::Vector2f{Game::width, Game::height}, z_index) {}

Image::Image(W& window, const sf::Texture* t, sf::Vector2f pos,
             sf::Vector2f size, Z_IND_T z_index)
    : Image{window, z_index} {
  auto g = getGraphic();
  // set size and position
  g->setSize(size);
  g->setPosition(pos);
  // set texture
  g->setTexture(t);
}

Image::G_TYPE_PTR Image::getGraphic() const {
  return static_cast<G_TYPE_PTR>(widget::getGraphic());
}

// BOX
Box::Box(W& window, Z_IND_T z_index) : widget(window, z_index) {}

Box::G_TYPE_PTR Box::getGraphic() const {
#ifndef CAST_DEBUG
  return static_cast<G_TYPE_PTR>(widget::getGraphic());
#else
  auto p = dynamic_cast<G_TYPE_PTR>(widget::getGraphic());
  assert(p);
  return p;
#endif
}

sf::Shape* Box::getGraphicElement() { return getGraphic(); }

void Box::setTexture(const sf::Texture* t,
                     sf::IntRect t_bound = sf::IntRect{
                         0, 0, 0, 0}) {      // by default it takes the full
  if (t_bound == sf::IntRect{0, 0, 0, 0}) {  // if the rectangle is the default
    sf::Vector2u size = t->getSize();
    // set texture to full size
    // Note: test wether the narrowing check is correctly performed
    t_bound = sf::IntRect{sf::Vector2i{0, 0}, sf::Vector2i{size}};
  }
  getGraphic()->setTexture(t);
  getGraphic()->setTextureRect(t_bound);
}

void Box::setPosition(sf::Vector2f& pos) { getGraphic()->setPosition(pos); }

// BUTTON
Button::Button(W& window, Z_IND_T z_index) : Box(window, z_index) {
  setClickHandler(std::function<void(void)>(
      []() { std::cout << "Hello world\n"; }));  // do nothing by default
  // cree an empty rectangle
  setGraphic(std::make_unique<sf::RectangleShape>());
}

Button::Button(W& window, sf::Vector2f pos, sf::Vector2f size,
               const sf::Texture* t, Z_IND_T z_index)
    : Button{window, z_index} {
  // set posotion
  getGraphic()->setPosition(pos);
  // set texture
  getGraphic()->setTexture(t);
  // set size
  getGraphic()->setSize(size);
}

// button graphic access
Button::G_OBJ_PTR Button::getGraphic() const {
  return static_cast<G_OBJ_PTR>(widget::getGraphic());
}

void Button::onClick(sf::Event const& e) {
  // check wether the left mouse button was clicked
  if (e.mouseButton.button == sf::Mouse::Left) {
    // if so, test wether the mouse cursor is over the object
    if (getGraphic()->getGlobalBounds().contains(e.mouseButton.x,
                                                 e.mouseButton.y)) {
      // call the handler if so
      clickHandler();
    }
  }
}

// TEXT LINE
TextLine::TextLine(W& window, sf::Vector2f pos, const char* txt, sf::Font& f,
                   sf::Color c, Z_IND_T z_index)
    : widget{window, z_index}, text_{txt} {
  auto textArea = new sf::Text(text_, f);

  textArea->setPosition(pos);
  textArea->setFillColor(c);
  setGraphic(textArea);
}
TextLine::TextLine(W& window, const char* txt, sf::Font& f, sf::Color c,
                   Z_IND_T z_index)
    : TextLine{window, {0, 0}, txt, f, c, z_index} {}

TextLine::TextLine(W& window, std::unique_ptr<sf::Text> textObj,
                   Z_IND_T z_index)
    : widget(window, z_index) {
  setGraphic(std::move(textObj));
}

// updating
void TextLine::update() {
  auto p = getGraphic();
  p->setString(text_);
}

TextLine::G_TYPE_PTR TextLine::getGraphic() const {
  return static_cast<G_TYPE_PTR>(widget::getGraphic());
}

std::string const& TextLine::getText() const { return text_; }

void TextLine::setText(std::string& txt) {
  text_ = txt;
  update();
}

void TextLine::setPosition(sf::Vector2f pos) { getGraphic()->setPosition(pos); }

sf::FloatRect TextLine::getLocalBounds() const {
  return getGraphic()->getLocalBounds();
}

// textButton

TextButton::TextButton(W& window, Z_IND_T z_index)
    : Button{window, z_index}, textObj_{new sf::Text()} {}

TextButton::TextButton(W& window, const char* txt, sf::Font& f,
                       sf::Texture const* t, sf::Color c, Z_IND_T z_index)
    : TextButton{window, z_index} {
  textObj_->setString(txt);
  textObj_->setFont(f);
  textObj_->setFillColor(c);
  // get bounding box
  auto bounds = textObj_->getGlobalBounds();
  // set minimal button size
  getGraphic()->setSize({bounds.width, bounds.height});
  getGraphic()->setPosition({bounds.left, bounds.top});
  getGraphic()->setTexture(t);
}

void TextButton::draw() const {
  // draw button
  widget::draw();
  // draw text
  getWindow().draw(*textObj_);
}

void TextButton::setPosition(sf::Vector2f& pos) {
  Box::setPosition(pos);
  textObj_->setPosition(pos);
}*/

}  // namespace IsoRPG