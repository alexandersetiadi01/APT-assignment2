#include "Tile.h"

#include <iostream>

Tile::Tile(){
   colour = ' ';
}

Tile::Tile(Colour _colour, Shape _shape)
{
   colour = _colour;
   shape = _shape;
}

// Tile::Tile(Tile& other) {
//    this->colour = other.colour;
//    this->shape = other.shape;
// }

// Tile::~Tile() {
// }

Colour Tile::getColour() {
   return colour;
}

Shape Tile::getShape() {
   return shape;
}
std::string Tile::getTile() {
    return std::string(colour + std::to_string(shape));
}
