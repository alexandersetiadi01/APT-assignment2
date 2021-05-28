#ifndef ASSIGN2_TILEBAG_H
#define ASSIGN2_TILEBAG_H

#include <istream>
#include <string>
#include <vector>

#include "Node.h"
#include "Tile.h"
#include "TileCodes.h"
#include "LinkedList.h"

#define MAX_TILEBAG_SIZE    108

class TileBag {

public:
    TileBag();
    TileBag(TileBag& other);
    ~TileBag();

    int size();


    //get tile at a specific count
    Tile* get(int count);

    //add a tile to the end of the tilebag list
    void add(Tile* tile);

    //add a tile to a specific count in the tilebag list
    void add(Tile* tile, int count);

    //remove a tile from the tilebag a given count
    void remove(int count);

    void clear();


private:

    LinkedList* tilebag;

};

#endif // ASSIGN1_TILEBAG_H
