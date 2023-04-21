#include "../../include/gameInterface/gameScreens.hpp"
#include "../../include/gameInterface/gameInterface.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <type_traits>

namespace IsoRPG {
// CLASSE WINDOW DISPLAY BASE
// windowDisplayBase::windowDisplayBase(W& window) w_{window} {}

windowDisplayBase::~windowDisplayBase() {}

Menu::Menu(W& window)
    : windowDisplayBase(window){};  // the default menu has no elements

// CLASS MENU
//

std::unique_ptr<BaseWidget> Menu::make_widget(std::string& data) {}

void Menu::addWidget(std::unique_ptr<BaseWidget>&& wid) {
  widgets_.insert(widgets_.end(), std::move(wid));
}

void Menu::onEvent(sf::Event const& e) {
  // call the click handler on each object
  std::for_each(
      widgets_.begin(), widgets_.end(), [e](std::unique_ptr<BaseWidget>& widget) {
        // call the function event dispatcher. Exception checking to be re written
        try {
          widget->onEvent(e);
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
                [](std::unique_ptr<BaseWidget> const& widget) { widget->draw(); });
}

void Menu::updateWidgets() {
  std::sort(widgets_.begin(),widgets_.end(),
      [](std::unique_ptr<BaseWidget> const& a, std::unique_ptr<BaseWidget> const& b) {
        // sort in ascending order by z index
        return a->getZIndex() < b->getZIndex();
      });
}

Menu::WIDGET_CONTAINER& Menu::getWidgets() { return widgets_; }

std::vector<std::unique_ptr<genericObject>>& Menu::getObjects() {
  return objects_;
}

// CLASS MAINMENU
MainMenu::MainMenu(W& window) : Menu(window), textureManager_{} {
  //reserve some space
  getWidgets().reserve(nReserve);
  // load textures
  try {
    textureManager_.load(Textures::ID::mainMenuBackground,
                         "background2.jpg");
    textureManager_.load(Textures::ID::mainButtonBackground,
                         "button_background.png");
    textureManager_.load(Textures::ID::characterPortrait,
                         "character_portrait.jpg");
    textureManager_.load(Textures::ID::playButton, "buttons.jpg");
    if (!f.loadFromFile("resources/fonts/gun4f.ttf")) {
      throw std::runtime_error("Couldn't load font!");
    }
  } catch (std::runtime_error& e) {
    std::cerr << e.what();
  }
  // load font
  /*
  // set background image
  addWidget(std::make_unique<Image>(
      w_, textureManager_.get(Textures::ID::mainMenuBackground), -1));

  // populate the main menu with objects
  addWidget(std::make_unique<Button>(
      w_, sf::Vector2f{(2200 - 300) / 2, 500}, sf::Vector2f{300, 100},
      textureManager_.get(Textures::ID::mainButtonBackground)));

  addWidget(std::make_unique<TextLine>(
      w_,
      sf::Vector2f{(2200 - 300) / 2 + 0.5 * (300 - 4 * 30),
                   500 + 0.5 * (100 - 30)},
      "Play", f, sf::Color::Yellow));

  {
    auto textPlay=std::unique_ptr<TextLine>(new TextLine{w_,"Test",f,sf::Color::Yellow});
    sf::Vector2f position{0,0};
    sf::FloatRect bounds=textPlay->getLocalBounds();
    position.x=(Game::width-bounds.width)/2;
    position.y=20;
    //better: add get width and height functions
    //even better: add texted button with alignment options
    textPlay->setPosition(position);
    addWidget(std::move(textPlay));
  }

  {  // create character name widget
    std::ifstream settings("settings.txt");
    std::string c_name{};
    settings >> c_name;
    c_name="User: "+c_name;

    sf::Vector2f ch_name_pos{0, 1200};  // temporary
    addWidget(std::make_unique<TextLine>(w_, ch_name_pos, c_name.c_str(), f,
                                         sf::Color::Yellow));

    // create character portrait
    addWidget(std::make_unique<Image>(
        w_, textureManager_.get(Textures::ID::characterPortrait),
        sf::Vector2f{50, 50}, sf::Vector2f{200, 300}));
  }

  {//create dummy button
  auto b=std::make_unique<TextButton>(w_,"Text",f,textureManager_.get(Textures::ID::mainButtonBackground));
  sf::Vector2f pos{};
  pos.x=Game::width-(b->getGraphicElement()->getGlobalBounds().width);
  pos.x/=2.;
  pos.y=300;
  b->setPosition(pos);
  addWidget(std::move(b));

  }
  */

  //create background image
  addWidget(std::make_unique<Widget<sf::RectangleShape>>(w_,[this](){
    //create shape to represent background image
    sf::RectangleShape s{sf::Vector2f{Game::width,Game::height}};
    //set position
    s.setPosition({0,0});
    //set texture
    s.setTexture(textureManager_.get(Textures::ID::mainMenuBackground));
    return s;
  },-1));

  //create main title
  addWidget(std::make_unique<Widget<sf::Text>>(w_,[this](){
    //sf::Vector2f{300,50},"IsoRPG",f,sf::Color::Green
    sf::Text t{"IsoRPG",f};
    t.setFillColor(sf::Color::Green);
    t.setPosition(sf::Vector2f{300,500});
    return t;
  }));

  //create play button
  addWidget(std::make_unique<Widget<sf::Sprite>>(w_,[this](){
    sf::Sprite s{*textureManager_.get(Textures::ID::playButton),{10,10,210,100}};

    return s;
  }));
  

  // sort widgets by z index
  updateWidgets();
}

}  // namespace IsoRPG