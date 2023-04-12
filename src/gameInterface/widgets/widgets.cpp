#include "../../../include/gameInterface/widgets/widgets.hpp"

#include <iostream>
#include <stdexcept>

#include "../../../include/gameInterface/gameInterface.hpp"

namespace IsoRPG {
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

// BUTTON
Button::Button(W& window, Z_IND_T z_index) : Box(window, z_index) {
  setClickHandler(std::function<void(void)>(
      []() { std::cout << "Hello world\n"; }));  // do nothing by default
}

Button::Button(W& window, sf::Vector2f pos, sf::Vector2f size,
               const sf::Texture* t, Z_IND_T z_index)
    : Button{window, z_index} {
  // create rectangle
  auto rect = new sf::RectangleShape{size};
  // set posotion
  rect->setPosition(pos);
  // set texture
  rect->setTexture(t);
  // add rectangle to the graphic object
  setGraphic(rect);
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

}  // namespace IsoRPG