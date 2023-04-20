#ifndef GAMEOBJECTS_HPP
#define GAMEOBJECTS_HPP

#include <SFML/Graphics.hpp>
#include <memory>

using W = sf::RenderWindow;

namespace IsoRPG{

template<class F, class... args>
void transform(F function, args... args);//wrapper function for transformations:
//1: function pointer to the sprite member function
//2: arguments
//note: if the transform function is not const, a const cast may be required

class basicGameObject{
    typedef sf::Sprite G_TYPE;
    typedef std::unique_ptr<G_TYPE> G_TYPE_PTR;
    typedef G_TYPE& G_TYPE_REF;
    typedef G_TYPE const& G_TYPE_CREF;

    W& w_;//window
    G_TYPE_PTR sprite_;//undelying sfml object
public:
    basicGameObject(W&);
    basicGameObject(W&,G_TYPE_PTR&&);

    virtual ~basicGameObject()=default;

    //graphics
    virtual void draw() const;

    //sfml object wrapper for transforming
    //essentially a transforbale, but forbids assignment
    /*class Transformable: public sf::Transformable{

        public:
            Transformable()=default;
            ~Transformable()=default;

            Transformable(Transformable const&)=delete;
            Transformable& operator=(Transformable const&)=delete;
            //Transformable(Transformable &&)=delete;
            //Transformable& operator=(Transformable &&)=delete;
    };*/
    //sfml object interface
    void setSprite(G_TYPE_PTR&&);
    G_TYPE_CREF getSprite() const;
    sf::Transformable& transform();
};

}


#endif