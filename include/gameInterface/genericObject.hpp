#ifndef GENERIC_OBJ_HPP
#define GENERIC_OBJ_HPP

#include <SFML/Graphics.hpp>

using W=sf::RenderWindow;

// CLASSE GENERIC OBJECT - oggetto generico SENZA RAPPRESENTAZIONE GRAFICA
//
// Contenuto
//
//

namespace IsoRPG{
    class genericObject{
        public:
            genericObject(){};
            virtual ~genericObject(){};

            virtual void draw() const =0;
            virtual bool update()=0;
    };
}



#endif