#ifndef GAME_SCREENS
#define GAME_SCREENS

#include <SFML/Graphics.hpp>

#include "genericObject.hpp"

using W=sf::RenderWindow;
// classe base per mostrare cose a schermo
// classe puramente astratta
//base assumption: this object's content cover all the window
// contenuti
//  1 - reference alla finestra: serve per disegnarci cose. deve essere accessibile alle sottoclassi

//funzioni protette
// 1 - display: scrivi sulla finestra i contenuti. 
//funzioni pubbliche
// costruttore: lancia il costruttore della classe base per inizializzare i suoi mmebri
// 2 - onUpdate: called by event loop. update internal state. does not imply a screen update, could be just called
//  as a result of an event needing to be passed to a member.
// base class implementation: pure virtual
// 3 - pushEvent



namespace IsoRPG
{
    //base class for showing stuff
    //
    //contents
    //
    //functions
    // display: the default display function checks wether any update has been made and if so, displays
    // onUpdate: takes a (yet to define) custom event object containing interface-related events
    // that must be processed by the objects displayed in the current view. Must be implemented



    class windowDisplayBase
    {
    protected: 
        W &w_;
        bool hasGraphicChanged_;

        virtual void display() const=0;

    public:
        explicit windowDisplayBase(W& window): w_{window}, hasGraphicChanged_{false} {};
        virtual ~windowDisplayBase();

        virtual void onUpdate()=0; //to do: add a objectUpdateEvent parameter. 
    };

    class windowDisplayHelloWorld: public windowDisplayBase{
        protected:
            virtual void display() const override;
        private:

        public:
            explicit windowDisplayHelloWorld(W& window): windowDisplayBase(window) {};

            virtual void onUpdate() override;
    };

    //MENU GENERICO
    //Funzionalita
    // display: draw the menu to the window. Can be done only if the menu is updated, so its protected
    // onUpdate: update the menu, passing events to the contained objects

    class Menu: public windowDisplayBase{
        protected:
            virtual void display() const override;
        private:

        public:
            explicit Menu(W& window): windowDisplayBase(window) {};
            
            virtual void onUpdate() override;
    };
}

#endif