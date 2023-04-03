#include "../../../include/gameInterface/widgets/widgets.hpp"

#include "../../../include/gameInterface/gameInterface.hpp"

#include <stdexcept>
#include <iostream>

namespace IsoRPG{
    //CLASS WIDGET
    widget::widget(W& window): w_{window}{}
    widget::~widget(){}

    //events
    void widget::onClick(sf::Event const& e){} //default implementation is empty
    void widget::setClickHandler(std::function<void(void)>&& h){clickHandler=h;}
    std::function<void(void)> const& widget::getClickHandler() const{return clickHandler;}

    //graphics
    void widget::setTextureID(Textures::ID id){
        t_id_=id;
    }

// CLASSE IMAGE

    Image::Image(W& window): widget(window),graphicElement_{new sf::RectangleShape()} {
    }

    Image::Image(W& window, const sf::Texture* t): widget(window),graphicElement_{new sf::RectangleShape()}{
        //TEMPORARY
        graphicElement_->setSize({Game::width,Game::height});
        //set texture
        graphicElement_->setTexture(t);
    }

    void Image::draw() const{
        w_.draw(*graphicElement_);
    }


    //BOX
    Box::Box(W& window): widget(window){}

    void Box::draw() const{
        w_.draw(*graphicElement_);
    }

    sf::Shape* Box::getGraphicElement(){
        return graphicElement_.get();
    }

    void Box::setTexture(const sf::Texture* t, sf::IntRect t_bound=sf::IntRect{0,0,0,0}){//by default it takes the full 
        if(t_bound==sf::IntRect{0,0,0,0}){//if the rectangle is the default
            sf::Vector2u size=t->getSize();
            //set texture to full size
            //Note: test wether the narrowing check is correctly performed
            t_bound=sf::IntRect{sf::Vector2i{0,0},sf::Vector2i{size}};
        }
        graphicElement_->setTexture(t);
        graphicElement_->setTextureRect(t_bound);
    }


    //BUTTON
    Button::Button(W& window): Box(window){
        setClickHandler(std::function<void(void)>([](){}));//do nothing by default

        sf::RectangleShape* sh=new sf::RectangleShape({300,100});
        sh->setPosition(500,700);
        graphicElement_=std::unique_ptr<sf::RectangleShape>(sh);
    }

    void Button::onClick(sf::Event const& e){
        //check wether the left mouse button was clicked
        if(e.mouseButton.button==sf::Mouse::Left){
            //if so, test wether the mouse cursor is over the object
            if(graphicElement_->getGlobalBounds().contains(e.mouseButton.x,e.mouseButton.y)){
                //call the handler if so
                clickHandler();
            }
        }
    }

}