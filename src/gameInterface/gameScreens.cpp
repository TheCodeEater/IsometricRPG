#include "../../include/gameInterface/gameScreens.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

namespace IsoRPG {
// CLASSE WINDOW DISPLAY BASE
// windowDisplayBase::windowDisplayBase(W& window) w_{window} {}

windowDisplayBase::~windowDisplayBase() {}

Menu::Menu(W& window)
    : windowDisplayBase(window){};  // the default menu has no elements

// CLASS MENU
//

std::unique_ptr<widget> Menu::make_widget(std::string& data) {}

void Menu::addWidget(std::unique_ptr<widget>&& wid) {
  widgets_.insert(widgets_.end(), std::move(wid));
}

void Menu::onClick(sf::Event const& e) {
  // call the click handler on each object
  std::for_each(
      widgets_.begin(), widgets_.end(), [e](std::unique_ptr<widget>& widget) {
        // call the click handler on the widget
        try {
          widget->onClick(e);
        } catch (std::bad_function_call& e) {
          std::cerr << e.what();
          std::cerr << "\nLikely the function object event handler isn't set "
                       "up correctly\n";
          std::cerr
              << "ERROR: action associated with the button not performed\n";
        }
      });
}

void Menu::display() const {
  // draw elements
  std::for_each(widgets_.begin(), widgets_.end(),
                [](std::unique_ptr<widget> const& widget) { widget->draw(); });
}

void Menu::updateWidgets() {
  widgets_.sort(
      [](std::unique_ptr<widget> const& a, std::unique_ptr<widget> const& b) {
        // sort in ascending order by z index
        return a->getZInd() < b->getZInd();
      });
}

Menu::WIDGET_CONTAINER& Menu::getWidgets() { return widgets_; }

std::vector<std::unique_ptr<genericObject>>& Menu::getObjects() {
  return objects_;
}

// CLASS MAINMENU
MainMenu::MainMenu(W& window) : Menu(window), textureManager_{} {
  // load textures
  try {
    textureManager_.load(Textures::ID::mainMenuBackground,
                         "main_menu_background.jpg");
    textureManager_.load(Textures::ID::mainButtonBackground,
                         "button_background.png");
    if (!f.loadFromFile("resources/fonts/gun4f.ttf")) {
      throw std::runtime_error("Couldn't load font!");
    }
  } catch (std::runtime_error& e) {
    std::cerr << e.what();
  }
  // load font

  // set background image
  addWidget(std::make_unique<Image>(
      w_, textureManager_.get(Textures::ID::mainMenuBackground)));

  // populate the main menu with objects
  addWidget(std::make_unique<Button>(
      w_, sf::Vector2f{(2200 - 300) / 2, 500}, sf::Vector2f{300, 100},
      textureManager_.get(Textures::ID::mainButtonBackground)));

  addWidget(std::make_unique<TextLine>(
      w_,
      sf::Vector2f{(2200 - 300) / 2 + 0.5 * (300 - 4 * 30),
                   500 + 0.5 * (100 - 30)},
      "Play", f, sf::Color::Yellow));

  // sort widgets by z index
  updateWidgets();
}

}  // namespace IsoRPG