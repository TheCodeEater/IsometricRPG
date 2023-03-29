#ifndef WIDGETS_HPP
#define WIDGETS_HPP

#include "../genericObject.hpp"

#include <SFML/Graphics.hpp>
#include <memory>

using W=sf::RenderWindow;

namespace IsoRPG {

    //CLASSE WIDGET - represent menu screen objects. pure abstract class
    // 
    //members
    //
    // 1 - sfml inner object - the one to be drawn. Unique ptr: the ownership is exclusive to this class
    


    class widget : public genericObject {
        protected:
            std::unique_ptr<sf::Drawable> graphicElement_;

        public:
            widget(W&);
            virtual ~widget();

            virtual void draw() const override;
            virtual bool update() override;

            //interface to access the drawable
    };
}  // namespace IsoRPG

#endif