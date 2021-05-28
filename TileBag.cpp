#include "TileBag.h"

TileBag::TileBag()
{
    tilebag = new LinkedList();
}

TileBag::TileBag(TileBag &other)
{
    tilebag = new LinkedList(*other.tilebag);
}

TileBag::~TileBag()
{
    delete tilebag;
}

int TileBag::size()
{
    return tilebag->size();
}

Tile *TileBag::get(int count)
{
    return tilebag->get(count);
}

void TileBag::add(Tile *tile)
{
    tilebag->add_back(tile);
}

void add(Tile *tile, int count)
{
    //TODO
}

void TileBag::remove(int count)
{
    tilebag->remove(count);
}

void TileBag::clear()
{
    tilebag->clear();
}