#include "../include/resourceLoader.hpp"

namespace IsoRPG {

void resourcesLoader::load(Textures::ID id, std::string const& filename, sf::IntRect r) {
  // build the path to the file
  std::string path = "resources/assets/" + filename;
  // open the file
  loadFromPath(id, path,r);
}

void resourcesLoader::loadFromPath(Textures::ID id, std::string const& path, sf::IntRect r) {
  T_ptr texture(new sf::Texture());
  //test wether r is all or not
  bool loaded{};
  if(r==sf::IntRect{0,0,0,0}){
    loaded=texture->loadFromFile(path);
  }else{
    loaded=texture->loadFromFile(path,r);
  }

  if (!loaded) {
    throw std::runtime_error("Resources Loader: cannot load " + path +
                             "\nCheck the working directory");
  } else {
    // if loading is successful, add to the map. Move the pointer ownership
    auto inserted = textures_.insert(std::make_pair(id, std::move(texture)));
    // test wether the resource was arleady loaded. Throw if not
    assert(inserted.second);
  }
}

const sf::Texture* resourcesLoader::get(Textures::ID id) {
  // get texture, extract raw pointer, return
  // to do: replace unique pointers with shared and weak (if possibile)
  return textures_.at(id).get();
}

}  // namespace IsoRPG
