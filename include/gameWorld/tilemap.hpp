#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <SFML/Graphics.hpp>
#include "tilesets.hpp"

using W = sf::RenderWindow;

namespace IsoRPG {

/////////////////
///
/// TILEMAP CLASS
///
/// Private members
/// vertices_ : the undelying sfml object containing the vertices
/// tiles_x, tiles_y : number of tiles for each axis
///
/// Constructor
/// creates the vertices array. Takes the number of tiles per axis, their size in pixels (must be the same for texture and screen), texture 
//////////////////////////////

class mapTile{//class to associate tilemap id to texture coordinates
    static std::map<Tiles::ID,sf::FloatRect> tiles_pos_;//tiles position
    public:
        mapTile()=default;
        sf::FloatRect operator() (Tiles::ID);
};

class Tilemap : public sf::Drawable,
                public sf::Transformable {
 private:
  sf::VertexArray vertices_;
  sf::Vector2u N_tiles_;
  float tileSize_;
  sf::Texture& texture_;

 public:
  Tilemap(sf::Vector2u n_tiles,float tileSize,sf::Texture const& texture);

  template<size_t x_, size_t y_>
    void Tilemap::mapTiles(std::array<std::array<Tiles::ID,x_>,y_> map);

  private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
}  // namespace IsoRPG

#endif