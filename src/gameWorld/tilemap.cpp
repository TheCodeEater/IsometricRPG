#include "../../include/gameWorld/tilemap.hpp"

namespace IsoRPG {
Tilemap::Tilemap(sf::Vector2u n_tiles,sf::Vector2u tileSize,sf::Texture const& texture)
    : N_tiles_{n_tiles}, tileSize_{tileSize}, texture_{const_cast<sf::Texture&>(texture)} {
        //calculate array size
        unsigned size=N_tiles_.x*N_tiles_.y*4;
        //initialize vertex array
        vertices_=sf::VertexArray{sf::Quads,size};
    }

    void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const{
        //set transformations
        states.transform *= getTransform();
        //set texture
        states.texture = &texture_;
        //actual draw
        target.draw(vertices_, states);
    }
}  // namespace IsoRPG