
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H
#include <string>
// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;

class Tile {
public:
   Tile();
   Tile(Colour, Shape);
   // Tile(Tile& other);
   // ~Tile();

   Colour getColour();
   Shape  getShape();


   std::string getTile();

   Colour colour;
   Shape  shape;
};

#endif // ASSIGN2_TILE_H
