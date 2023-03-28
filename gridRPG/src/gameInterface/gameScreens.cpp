#include "../../include/gameInterface/gameScreens.hpp"

namespace IsoRPG
{
    // CLASSE WINDOW DISPLAY BASE
    //windowDisplayBase::windowDisplayBase(W& window) w_{window} {}
    
    windowDisplayBase::~windowDisplayBase(){}
    //
    void windowDisplayBase::display() const
    {
        // clear the window, then draw it
        w_.clear(sf::Color::Black);
        w_.display();
    }

    // CLASSE WINDOW DISPLAY HELLO WORLD
    void windowDisplayHelloWorld::display() const
    {
        w_.clear(sf::Color::Black);

        sf::CircleShape shape(50.f);
        // set the shape color to green
        shape.setFillColor(sf::Color(100, 250, 50));

        w_.draw(shape);

        w_.display();
    }
    void windowDisplayHelloWorld::onUpdate()
    {
        // display the phrase
        display();
    }
}