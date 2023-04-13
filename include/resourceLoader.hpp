#ifndef RESOURCES_HPP
#define RESOURCES_HPP

// this file contains the various texture locations
#include <SFML/Graphics.hpp>
#include <fstream>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include "gameWorld/tilesets.hpp"

namespace IsoRPG {
namespace Textures {
enum class ID { mainButtonBackground = 0, mainMenuBackground = 1, characterPortrait=2 };
}

class resourcesLoader {
  typedef std::unique_ptr<sf::Texture> T_ptr;

  std::map<Textures::ID, T_ptr> textures_;

 public:
  resourcesLoader() = default;
  resourcesLoader(resourcesLoader const&) = delete;
  resourcesLoader(resourcesLoader&&) = delete;
  resourcesLoader operator=(resourcesLoader const&) = delete;
  resourcesLoader operator=(resourcesLoader&&) = delete;

  void load(Textures::ID, std::string const&);
  void loadFromPath(Textures::ID, std::string const&);

  const sf::Texture* get(Textures::ID);

  //mapping tile enums to R2 vectors
  //static std::map<Tiles::ID,sf::Vector2u> til
};

}  // namespace IsoRPG

#endif