#include "../../include/gameInterface/gameScreens.hpp"

#include <algorithm>
#include <iostream>

namespace IsoRPG {
// CLASSE WINDOW DISPLAY BASE
// windowDisplayBase::windowDisplayBase(W& window) w_{window} {}

windowDisplayBase::~windowDisplayBase() {}

Menu::Menu(W& window)
    : windowDisplayBase(window){};  // the default menu has no elements

// CLASS MENU

void Menu::onClick(sf::Event const& e){
  //call the click handler on each object
  std::for_each(widgets_.begin(),widgets_.end(),[e](std::unique_ptr<widget> & widget){
    //call the click handler on the widget
    widget->onClick(e);
  });
}

void Menu::display() const {
  // draw elements
  std::for_each(widgets_.begin(), widgets_.end(),
                [](std::unique_ptr<widget> const& widget) { widget->draw(); });

}

std::vector<std::unique_ptr<widget>>& Menu::getWidgets(){
  return widgets_;
}

std::vector<std::unique_ptr<genericObject>>& Menu::getObjects(){
  return objects_;
}

// CLASS MAINMENU
MainMenu::MainMenu(W& window) : Menu(window), textureManager_{} {
    //load textures
    textureManager_.load(Textures::ID::mainMenuBackground,"main_menu_background.jpg");
    textureManager_.load(Textures::ID::mainButtonBackground,"button_background.png");
    //set background image
    widgets_.push_back(std::make_unique<Image>(w_,textureManager_.get(Textures::ID::mainMenuBackground)));

    
    //create the dummy button
    std::unique_ptr<Button> b(new Button(w_));
    b->setClickHandler([](){std::cout<<"Hello world!";});
    //set appropriate position
    auto e=b->getGraphicElement();
    e->setPosition((2200-150)/2,500);//centra orizzonatlmente
    
    //forgive me, it is just a test
    sf::Texture* t=new sf::Texture();
    t->setSmooth(true);
    t->loadFromFile("resources/assets/button_background.png");
    b->setTexture(t,{0,0,0,0});
    
    //populate the main menu with objects
    widgets_.push_back(std::move(b));
}

}  // namespace IsoRPG