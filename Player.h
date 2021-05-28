#include "Node.h"
#include "Tile.h"
#include "TileBag.h"
#include "TileCodes.h"

/**
 * Represents a single player in Qwirkle.
 */
class Player {
public:

   Player(int playerNo);
   ~Player();

   //Make it random
   void setInitialHand(TileBag* tilebag);

   int getPlayerNo();

private:
   //This line gives error
   int playerNo;

   TileBag* hand;


};
