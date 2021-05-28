#include "Player.h"

#include <iostream>
#include <random>

Player::Player(int playerNo) : playerNo(playerNo)
{
    hand = new TileBag();
}

Player::~Player()
{
    delete hand;
}

void Player::setInitialHand(TileBag *tilebag)
{
    delete hand;
    hand = new TileBag(*tilebag);
}

int Player::getPlayerNo()
{
    return -1;
}
