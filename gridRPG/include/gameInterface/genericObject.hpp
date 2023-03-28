#ifndef GENERIC_OBJ_HPP
#define GENERIC_OBJ_HPP

#include <SFML/Graphics.hpp>

using W=sf::RenderWindow;

// CLASSE GENERIC OBJECT - oggetto generico che può essere rappresentato
//
// Contenuto
//
//

namespace IsoRPG{
    class genericObject{
        protected:
            W& w_;
        private:

        public:
            explicit genericObject(W& window): w_{window} {};
            virtual ~genericObject();

            virtual void draw()=0;
            virtual void update()=0;
    };
}



#endif