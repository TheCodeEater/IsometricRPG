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
    // w_ window, used to draw objects. SFML object
    // Texture ID: texture id based on the enum class
    // graphicElement_ : the underlying generic graphic objects
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
        typedef sf::Drawable G_OBJ;
        typedef std::unique_ptr<G_OBJ> G_OBJ_PTR;//define alias for the underlying graphic object

        private:
            G_OBJ_PTR graphicObject_;
            W& w_;
        protected:
            Textures::ID t_id_;

            virtual G_OBJ* getGraphic() const;
            void setGraphic(G_OBJ*);
            void setGraphic(G_OBJ_PTR&&);

            //interface for updating graphic object based on data members
            virtual void update();

            //event handler
            std::function<void(void)> clickHandler;

        public:
            widget(W&);
            virtual ~widget()=0;
            //graphic
            void draw() const;
            
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
        typedef sf::RectangleShape G_OBJ;
        typedef G_OBJ* G_TYPE_PTR;

        protected:
            G_OBJ* getGraphic() const override;
        public:
            Image(W&);
            Image(W&, const sf::Texture*);

        
    };
    class Box: public widget{
        typedef sf::Shape* G_TYPE_PTR;

        protected:
            G_TYPE_PTR getGraphic() const override;
        public:
            Box(W&);

            //graphic maipulation
            sf::Shape* getGraphicElement();

            void setTexture(const sf::Texture*,sf::IntRect);
    };

    class Button: public Box{
        protected:

        public:
            Button(W&);
            Button(W& window, sf::Vector2f pos,sf::Vector2f size, const sf::Texture* t);

            //events
            virtual void onClick(sf::Event const&) override;
     };

     class TextLine: public widget{
        typedef char C_TYPE;
        typedef sf::Text* G_TYPE_PTR;

        private:
            std::string text_;
        protected:
            G_TYPE_PTR getGraphic() const override;

            //for updating internal status based on data members
            void update() override;
        public:
            TextLine(W& window, sf::Vector2f pos, const char* txt,sf::Font& f,sf::Color c=sf::Color::Black);

            void setText(std::string& txt);
            std::string const& getText() const;

     };

}  // namespace IsoRPG

#endif