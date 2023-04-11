#ifndef GAME_SCREENS
#define GAME_SCREENS

#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <vector>
#include <list>
#include <utility>

#include "../resourceLoader.hpp"
#include "genericObject.hpp"
#include "widgets/widgets.hpp"

using W = sf::RenderWindow;
// classe base per mostrare cose a schermo
// classe puramente astratta
// base assumption: this object's content cover all the window
// contenuti
//  1 - reference alla finestra: serve per disegnarci cose. deve essere
//  accessibile alle sottoclassi

// funzioni protette
//  1 - display: scrivi sulla finestra i contenuti.
// funzioni pubbliche
//  costruttore: lancia il costruttore della classe base per inizializzare i
//  suoi mmebri 2 - onUpdate: called by event loop. update internal state. does
//  not imply a screen update, could be just called
//   as a result of an event needing to be passed to a member.
//  base class implementation: pure virtual
//  3 - pushEvent

namespace IsoRPG {
// base class for showing stuff
//
// contents
//
// functions
//  display: the default display function checks wether any update has been made
//  and if so, displays onUpdate: takes a (yet to define) custom event object
//  containing interface-related events that must be processed by the objects
//  displayed in the current view. Must be implemented

class windowDisplayBase {
 protected:
  W& w_;

 public:
  explicit windowDisplayBase(W& window) : w_{window} {};
  virtual ~windowDisplayBase();

  virtual void display() const = 0;
  virtual void onClick(sf::Event const&) = 0;
};
// MENU GENERICO
// Funzionalita
//  display: draw the menu to the window. Can be done only if the menu is
//  updated, so its protected onUpdate: update the menu, passing events to the
//  contained objects
//
//  MEMBRI VARIABILE
//
//  1 - Oggetti del menu (elements_): to be set up by constructor

class Menu : public windowDisplayBase {
  typedef std::list<std::unique_ptr<widget>> WIDGET_CONTAINER ;

   WIDGET_CONTAINER widgets_;
 protected:
  std::vector<std::unique_ptr<genericObject>> objects_{};

  //widget accessing interface
  std::unique_ptr<widget> make_widget(std::string& data);
  
  void add_widget(std::unique_ptr<widget>&&);
  

 public:
  explicit Menu(W& window);

  // events
  virtual void onClick(sf::Event const&) override;

  // graphics
  virtual void display() const override;

  // member access
  WIDGET_CONTAINER& getWidgets();
  std::vector<std::unique_ptr<genericObject>>& getObjects();
};

class MainMenu : public Menu {
  resourcesLoader textureManager_;
  sf::Font f;  // temporary
 public:
  MainMenu(W& window);

  // initial setup not overridden, uses the base class
};
}  // namespace IsoRPG

#endif