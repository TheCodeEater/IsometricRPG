#include "../../include/gameInterface/gameInterface.hpp"

#define dummy

namespace IsoRPG
{

    // CLASS GAME
    Game::Game(){
        w_.create(sf::VideoMode(width, height), windowTitle);
        w_.setVerticalSyncEnabled(true);
        #ifdef dummy
            currentWindow_=std::make_unique<windowDisplayHelloWorld>(w_);
        #endif
    }
    Game::~Game()
    {
        w_.close();
    }

    int Game::loop(){
        //execute dummy
        currentWindow_->onUpdate();
        //event loop
        while(w_.isOpen()){

            //handle event loop
            sf::Event e;
            while(w_.pollEvent(e)){

                switch(e.type){
                    case sf::Event::Closed :
                        w_.close();
                        break;
                    default:
                        break;
                }

            }

        }
        return 0;
    }

}
