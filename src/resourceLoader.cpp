#include "../include/resourceLoader.hpp"

namespace IsoRPG{

    void resourcesLoader::load(Textures::ID id, std::string const& filename){
        //build the path to the file
        std::string path="resources/assets/"+filename;
        //open the file
        T_ptr texture(new sf::Texture());
        if(!texture->loadFromFile(path)){
            throw std::runtime_error("Resources Loader: cannot load "+path+"\nCheck the working directory");
        }else{
            //if loading is successful, add to the map. Move the pointer ownership
            auto inserted=textures_.insert(std::make_pair(id,std::move(texture)));
            //test wether the resource was arleady loaded. Throw if not
            assert(inserted.second);
        }
    }

    const sf::Texture* resourcesLoader::get(Textures::ID id){
        //get texture, extract raw pointer, return 
        //to do: replace unique pointers with shared and weak (if possibile)
        return textures_.at(id).get();
    }

}

