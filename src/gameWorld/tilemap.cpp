#include "../../include/gameWorld/tilemap.hpp"

namespace IsoRPG {

Matrix::Matrix(int n_rows, int n_cols): cols_{n_cols}, rows_{n_rows}{
    //set vector size
    tiles_.reserve(cols_*rows_);
}

Matrix::Tile const& Matrix::at(int row, int col) const{
    assert(tiles_.max_size()==cols_*rows_); //test wether the size is correct
    return tiles_.at(row*cols_+col); 
}

Matrix::Tile& Matrix::operator()(int row, int col){
    assert(tiles_.max_size()==cols_*rows_); //test wether the size is correct
    return tiles_.at(row*cols_+col); //offset by row* elements in row (ie cols) to the 1st element of the right row, then apply comun offset
}


Tilemap::Tilemap(sf::Vector2u n_tiles,float tileSize,sf::Texture const& texture)
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

    /*template<size_t x_, size_t y_>
    void Tilemap::mapTiles(std::array<std::array<Tiles::ID,x_>,y_> map){//set texture to the various tiles
        
        int i{};
        for(auto const& row: map){
            int j{};
            for(auto const& col: row){
                //set tile positions
                //get a quad
                //j sets the column offset, i*widh the row (remember: vertices are arranged in a line but we tret it as a 2d matrix)
                //x4: the array contains the 4 vertices of the quad, therefore for each quad there are 4 elements
                //i* tiles per row
                sf::Vertex* quad=&vertices_[(j + i * x_) * 4];
                //set position
                {
                sf::Vector2f topLeft{i*tileSize_,j*tileSize_};
                quad[0].position=topLeft;
                quad[1].position=topLeft+sf::Vector2f{tileSize_,0};
                quad[2].position=topLeft+sf::Vector2f{tileSize_,tileSize_};
                quad[3].position=topLeft+sf::Vector2f{0,tileSize_};
                }
                //set texture coordinates
                {
                    sf::Vector2f topLeft{};
                }
                ++j;
            }
            ++i;
        }
    }*/
}  // namespace IsoRPG