
#ifndef ASSIGN2_UTILS_H
#define ASSIGN2_UTILS_H

#include "Tile.h"

#include <fstream>

class TileBag;

/*
 * CAREFUL NOTES!
 * 
 * As dicsussed in the workshop, you can convert all of the print
 * methods to use an output stream.
 * Completing this implementation is left as an activity for yourself!
 */

void printAllTiles(std::ostream& output, Tile* tiles[], int numPrint);
void printAllTiles(Tile* tiles[], int numPrint);

void printTilebag(TileBag* tilebag);
void printTilebag(std::ostream& out, TileBag* tilebag);

void printHand(TileBag* tilebag);
void printHand(std::ostream& out, TileBag* tilebag);

void printTile(std::ostream& output, Tile* tile);
void printTile(Tile* tile);



#endif // UTILS_H
