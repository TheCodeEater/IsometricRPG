#ifndef WIDGETS_HPP
#define WIDGETS_HPP

// #include "../genericObject.hpp"

#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>
#include <string>

#include "../../resourceLoader.hpp"

using W = sf::RenderWindow;

namespace IsoRPG {

// CLASSE WIDGET - represent menu screen objects. pure abstract class
//
// members
//
//  w_ window, used to draw objects. SFML object
//  Texture ID: texture id based on the enum class
//  graphicElement_ : the underlying generic graphic objects
//
// FUNCTIONS
//  draw: draw the object. Subclass implement it in their own way, as each
//  widget has a different underlying object onClick: called by the window
//  owning the object. handles click event
//
// setClickHandler: set a click handler. Accepts an rvalue reference to a
// function object (forces the object to be move: you cannot assign the same
// function object to more objects)
//
// getClickHandler: return a const reference to the handler
//

// base widget class
class BaseWidget {
  // struct for safe SFML window access
  class WindowWrapper {
    W& w_;

   public:
    explicit WindowWrapper(W& window);
    void draw(const sf::Drawable& drawable) const;
  };
  // Z index: determines order of drawing and overlapping
  short zIndex_{};

  // SFML window
  WindowWrapper w_;

  //specific event handlers

 protected:
  // specific event handlers - default empty. 
  virtual void onClick(sf::Event const&);
  virtual void onMouseMove(sf::Event const&);
  virtual void onKeyPressed(sf::Event const&);

  // window access
  BaseWidget::WindowWrapper const& getWindow() const;

 public:
  BaseWidget(W& window, short z_index = 0);

  // special functions
  virtual ~BaseWidget() = default;
  BaseWidget& operator=(BaseWidget const&) = delete;
  BaseWidget& operator=(BaseWidget&&) = delete;
  BaseWidget(BaseWidget const&) = delete;
  BaseWidget(BaseWidget&&) = delete;

  // draw function, specific to each widget
  virtual void draw() const = 0;

  // geometric transforming functions
  virtual void setPosition(const sf::Vector2f pos) = 0;
  virtual sf::Vector2f getPosition() const = 0;

  // z index function
  void setZIndex(short);
  short getZIndex() const;

  // event handling function; called to receive an event
  virtual void onEvent(sf::Event const&);
};

// class to implement single-SFML object based widgets
// template as several types of SFML objects may be drawn
template <class graphic_object>
class Widget : public BaseWidget {
  // test wether is an SFML object - to be implemented

 private:
  // underlying sfml graphic object
  graphic_object graphicObject_;
public:
  Widget(W& window, short z_index = 0);  // default constructor.
  Widget(W& window, graphic_object&& graphic,
         short z_index = 0);  // takes an object to be moved: the user will not
                              // have the private object in its hands
  // Widget(W& window, graphic_object graphic, short z_index=0);//pass by value.
  // The user won't have the private object but causes copy overhead
  Widget(W& window, std::function<void(GraphicWrapper&)> processFunc,
         short z_index = 0);  // perform computation on the graphicObject
  //accepts function that create the object and returns it by value
  //the returned object is a different one (a copy) of the one processed inside the function
  Widget(W& window, std::function<graphic_object(void)> processFunc, short z_index=0);

  // drawing
  void draw() const final;

  // transforming - shall not be overridden in subclasses
  void setPosition(const sf::Vector2f pos) final;
  sf::Vector2f getPosition() const final;

  // struct to safely manipulate graphic_object
  // template<class graphic_object>
  class GraphicWrapper {
    graphic_object& gObj_;

   public:
    explicit GraphicWrapper(graphic_object& g);

    ~GraphicWrapper()=default;
    //disable copy and move
    GraphicWrapper(GraphicWrapper const&)=delete;
    GraphicWrapper(GraphicWrapper &&)=delete;
    GraphicWrapper& operator=(GraphicWrapper const&)=delete;
    GraphicWrapper& operator=(GraphicWrapper &&)=delete;

    void assign(graphic_object&& g);
  };
};
/*
class widget {
  typedef sf::Drawable G_OBJ;
  typedef std::unique_ptr<G_OBJ>
      G_OBJ_PTR;  // define alias for the underlying graphic object

 protected:
  typedef short Z_IND_T;
  Textures::ID t_id_;

  virtual G_OBJ* getGraphic() const;
  void setGraphic(G_OBJ*);
  void setGraphic(G_OBJ_PTR&&);

  // window interaction
  W& getWindow() const;

  // interface for updating graphic object based on data members
  virtual void update();

  // event handler
  std::function<void(void)> clickHandler;

 private:
  G_OBJ_PTR graphicObject_;
  W& w_;
  Z_IND_T z_index_{};

 public:
  widget(W&, Z_IND_T zindex = 0);
  virtual ~widget() = 0;
  // graphic
  virtual void draw() const;

  // graphic positioning
  Z_IND_T getZInd() const;
  void setZInd(Z_IND_T value);

  // managing graphics
  void setTextureID(Textures::ID);

  // events
  virtual void onClick(sf::Event const&);

  // event handlers
  void setClickHandler(std::function<void(void)>&&);
  std::function<void(void)> const& getClickHandler() const;
};

class Box : public widget {
  typedef sf::Shape* G_TYPE_PTR;

 protected:
  G_TYPE_PTR getGraphic() const override;

 public:
  Box(W&, Z_IND_T z_index = 0);

  // graphic maipulation
  sf::Shape* getGraphicElement();

  void setTexture(const sf::Texture*, sf::IntRect);

  // position setting
  virtual void setPosition(sf::Vector2f&);
};

// CLASS IMAGE: represents an image that can be drawn inside a rectangle
//
// Members
//
// Graphic element: the graphic object that contains the image
//
////////////////////////////

class Image : public Box {
  typedef sf::RectangleShape G_OBJ;
  typedef G_OBJ* G_TYPE_PTR;

 protected:
  G_TYPE_PTR getGraphic() const override;

 public:
  Image(W&, Z_IND_T);
  Image(W&, const sf::Texture*, Z_IND_T z_index = 0);
  Image(W&, const sf::Texture*, sf::Vector2f pos, sf::Vector2f size,
        Z_IND_T z_index = 0);
};

class Button : public Box {
  typedef sf::RectangleShape G_OBJ;
  typedef G_OBJ* G_OBJ_PTR;

 protected:
  G_OBJ_PTR getGraphic() const override;

 public:
  Button(W&, Z_IND_T);
  Button(W& window, sf::Vector2f pos, sf::Vector2f size, const sf::Texture* t,
         Z_IND_T z_index = 0);
  // Button(W& window, const sf::Texture* t, Z_IND_T z_index=0);

  // events
  virtual void onClick(sf::Event const&) override;
};

class TextLine : public widget {
  typedef char C_TYPE;
  typedef sf::Text* G_TYPE_PTR;

 private:
  std::string text_;

 protected:
  G_TYPE_PTR getGraphic() const override;

  // for updating internal status based on data members
  void update() override;

 public:
  TextLine(W& window, sf::Vector2f pos, const char* txt, sf::Font& f,
           sf::Color c = sf::Color::Black, Z_IND_T z_index = 0);
  TextLine(W& window, const char* txt, sf::Font& f,
           sf::Color c = sf::Color::Black, Z_IND_T z_index = 0);
  TextLine(W& window, std::unique_ptr<sf::Text>, Z_IND_T z_index = 0);

  void setText(std::string& txt);
  std::string const& getText() const;

  void setPosition(sf::Vector2f);

  sf::FloatRect getLocalBounds() const;
};

class TextButton : public Button {
 private:
  std::unique_ptr<sf::Text> textObj_;

 public:  // place the button by default in (0,0). Size depends on text size
  TextButton(W&, Z_IND_T);
  TextButton(W&, const char* txt, sf::Font& f, sf::Texture const* t,
             sf::Color c = sf::Color::Black, Z_IND_T z_index = 0);

  // drawing function
  void draw() const override;

  // positioning
  void setPosition(sf::Vector2f&) override;
};*/

}  // namespace IsoRPG

#endif