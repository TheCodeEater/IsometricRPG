#include "../../../include/gameInterface/widgets/widgets.hpp"

#include <stdexcept>

namespace IsoRPG{
    //CLASS WIDGET
    widget::widget(W& window): genericObject{window}{
        graphicElement_=std::make_unique<sf::CircleShape>(50.0f);
        // set the shape color to green
        if(auto circle= dynamic_cast<sf::Shape*>(graphicElement_.get())){
            circle->setFillColor(sf::Color(100, 250, 50));
        }else{
            throw std::runtime_error("Cannot draw an object of the base abstract class");
        }
    }
    widget::~widget(){}
    void widget::draw() const{
        //draw element on the window
        w_.draw(*graphicElement_);
    }
    bool widget::update(){
        //a generic widget has no special update features
        return false;
    }
}