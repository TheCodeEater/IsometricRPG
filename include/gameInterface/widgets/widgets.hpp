#ifndef WIDGETS_HPP
#define WIDGETS_HPP

//#include "../genericObject.hpp"

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <functional>

#include "../../resourceLoader.hpp"

using W=sf::RenderWindow;

namespace IsoRPG {

    //CLASSE WIDGET - represent menu screen objects. pure abstract class
    // 
    //members
    //
    // w_ window, used to draw objects
    // event handlers: std::function objects containing function pointers to the event handlers
    // 
    //FUNCTIONS
    // draw: draw the object. Subclass implement it in their own way, as each widget has a different underlying object
    // onClick: called by the window owning the object. handles click event
    //
    //setClickHandler: set a click handler. Accepts an rvalue reference to a function object 
    //(forces the object to be move: you cannot assign the same function object to more objects)
    //
    //getClickHandler: return a const reference to the handler
    //
    class widget{
        protected:
            W& w_;
            Textures::ID t_id_;

            //event handler
            std::function<void(void)> clickHandler;

        public:
            widget(W&);
            virtual ~widget();
            //graphic
            virtual void draw() const=0;
            
            //managing graphics
            void setTextureID(Textures::ID);
            
            //events
            virtual void onClick(sf::Event const&);

            //event handlers
            void setClickHandler(std::function<void(void)>&&);
            std::function<void(void)> const& getClickHandler() const;
    };
    

    //CLASS IMAGE: represents an image that can be drawn inside a rectangle
    //
    //Members
    //
    //Graphic element: the graphic object that contains the image
    //
    ////////////////////////////

    class Image: public widget{

        private:
            std::unique_ptr<sf::RectangleShape> graphicElement_;
        public:
            Image(W&);
            Image(W&, const sf::Texture*);

            //graphic
            virtual void draw() const override;

        
    };
    class Box: public widget{
        protected:
            std::unique_ptr<sf::RectangleShape> graphicElement_;
        public:
            Box(W&);

            virtual void draw() const override;

            //graphic maipulation
            sf::Shape* getGraphicElement();

            void setTexture(const sf::Texture*,sf::IntRect);
    };

    class Button: public Box{
        protected:

        public:
            Button(W&);

            //events
            virtual void onClick(sf::Event const&) override;
     };

}  // namespace IsoRPG

#endif