#include "../../include/gameInterface/gameInterface.hpp"

#include <cassert>

namespace IsoRPG
{

    // CLASS GAME
    Game::Game(){
        w_.create(sf::VideoMode(width, height), windowTitle);
        w_.setVerticalSyncEnabled(true);
    }
    Game::~Game()
    {
        w_.close();
    }

    int Game::loop(){
        //make sure the first screen is initialized
        assert(currentWindow_);
        //event loop
        while(w_.isOpen()){

            //handle event loop
            sf::Event e;
            while(w_.pollEvent(e)){

                switch(e.type){
                    case sf::Event::Closed :
                        w_.close();
                        break;
                    case sf::Event::MouseButtonReleased :
                        currentWindow_->onClick(e); //TEMPORARY IMPLEMENTATION, TO REMOVE ASAP
                    default:
                        break;
                }

            }
            //update the frame
            w_.clear(sf::Color::Black);
            currentWindow_->display();
            w_.display();

        }
        return 0;
    }

    void Game::setCurrentWindow(windowDisplayBase* screen){
        currentWindow_=std::unique_ptr<windowDisplayBase>(screen);
    }

    windowDisplayBase* Game::getCurrentWindow(){
        return currentWindow_.get();
    }

    sf::RenderWindow& Game::getSFMLWindow(){
        return w_;
    }


}
