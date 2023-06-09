#ifndef RESOURCES_HPP
#define RESOURCES_HPP

//this file contains the various texture locations
#include <SFML/Graphics.hpp>

#include <map>
#include <memory>
#include <string>
#include <fstream>
#include <stdexcept>

namespace IsoRPG{
    namespace Textures{
        enum class ID {
            mainButtonBackground=0,
            mainMenuBackground=1
        };
    }


class resourcesLoader{
    typedef std::unique_ptr<sf::Texture> T_ptr;

    std::map<Textures::ID,T_ptr> textures_;

    public:
        resourcesLoader()=default;
        resourcesLoader(resourcesLoader const&)=delete;
        resourcesLoader(resourcesLoader&&)=delete;
        resourcesLoader operator=(resourcesLoader const&)=delete;
        resourcesLoader operator=(resourcesLoader&&)=delete;

        void load(Textures::ID,std::string const&);

        const sf::Texture* get(Textures::ID);

};

}

#endif