#ifndef GAME_INTERFACE
#define GAME_INTERFACE

#include <string>
#include <memory>

#include <SFML/Graphics.hpp>

#include "gameScreens.hpp"

using W=sf::RenderWindow;

// header per l'interfaccia di gioco base
// Contenuti:
//  1 - classe game, che gestisce l'istanza generale del gioco

// CLASSE GAME
// Contenuti
//  1 - finestra
//  2 - schermata attuale. puntatore unico, solo io posso controllarla

namespace IsoRPG
{

    class Game
    {
        W w_;
        std::unique_ptr<windowDisplayBase> currentWindow_;

    public:
        static inline int width = 2200;
        static inline int height = 1600;
        static inline std::string windowTitle = "gioco fallito";

        Game();
        Game(Game const &) = delete;
        Game(Game &&) = delete;
        Game &operator=(Game const &) = delete;
        Game &operator=(Game &&) = delete;
        ~Game();

        int loop();
    };

}

#endif