
#include "utils.h"

#include "TileBag.h"

#include <iostream>
#include <fstream>

void printTilebag(TileBag *tilebag)
{
   printTilebag(std::cout, tilebag);
}

void printTilebag(std::ostream &out, TileBag *tilebag)
{
   for (int i = 0; i < tilebag->size(); ++i)
   {
      out << "Index: "
          << i << ": ";
      if (tilebag->get(i) != nullptr)
      {
         printTile(out, tilebag->get(i));
      }
   }
}

void printHand(TileBag *tilebag)
{
   printHand(std::cout, tilebag);
}

void printHand(std::ostream &out, TileBag *tilebag)
{
   for (int i = 0; i < tilebag->size(); ++i)
   {
      if (tilebag->get(i) != nullptr)
      {
         printTile(out, tilebag->get(i));
      }
   }
}

void printTile(std::ostream &output, Tile *tile)
{
   output << " ";
   output << tile->getColour()
          << tile->getShape() << " ";
}

void printTile(Tile *tile)
{
   printTile(std::cout, tile);
}
