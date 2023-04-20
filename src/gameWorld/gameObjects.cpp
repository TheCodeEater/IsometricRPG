#include "../../include/gameWorld/gameObjects.hpp"

namespace IsoRPG{

    template<class F, class... args>
        void transform(F function, args... args){
            function(&args...);
        }

    //basicGameObject class

    //construct basic game object from window and sprite
    basicGameObject::basicGameObject(W& window,G_TYPE_PTR&& sprite_ptr): w_{window}, sprite_{std::move(sprite_ptr)} {}

    //construct basic game object from window. A default empty sprite is created
    basicGameObject::basicGameObject(W& window): basicGameObject(window, std::make_unique<G_TYPE>()) {}

    void basicGameObject::draw() const{//draw the sprite
        w_.draw(*sprite_);
    }

    void basicGameObject::setSprite(G_TYPE_PTR&& sp){//set a new sprite. Old one deleted by smart pointers
        sprite_=std::move(sp);
    }

    basicGameObject::G_TYPE_CREF basicGameObject::getSprite() const{
        return *sprite_;
    }

    sf::Transformable& basicGameObject::transform(){
        return *sprite_;
    }
//basicGameObject::Transformable::Transformable(): sf::Transformable{}{}
}