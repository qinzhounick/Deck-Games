#pragma once
#include "Game.h"
#include "PinochleDeck.h"
#include "CardSet.h"

class PinochleGame: public Game{
    protected:
        PinochleDeck pinochleDeck;
        std::vector< CardSet<PinochleRank, Suit> > pinochleHands;
        virtual void deal();
    public:
        PinochleGame(int argc, const char * argv[]);
        virtual int play();
};