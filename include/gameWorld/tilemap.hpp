#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <SFML/Graphics.hpp>
#include "tilesets.hpp"
#include <memory>
#include "gameObjects.hpp"

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

class Matrix{//class to represent the game world
  struct Tile; // the generic world tile struct

  int cols_{};//geometric structure
  int rows_{};
  std::vector<Tile> tiles_;//vector of tile data
  
  //tilemap

  public:
    Matrix()=default;
    Matrix(int n_rows, int n_cols);//constructor

    Tile const& at(int row, int col) const;//tile access read only

    Tile& operator() (int row, int col);//tile access modifying
};

enum class phase{
  Solid, Liquid, Gas, Steam, Plasma
};

struct Matrix::Tile{//struct to represent a tile
  bool occupied_{};//is occupied
  bool walkable_{};//can be walked on
  phase p{phase::Solid};//state of matter

  std::weak_ptr<basicGameObject> object_; //pointer to the object (if any. if no object are there, it is nullptr)
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

  //template<size_t x_, size_t y_>
    //void Tilemap::mapTiles(std::array<std::array<Tiles::ID,x_>,y_> map);

  private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
}  // namespace IsoRPG

#endif