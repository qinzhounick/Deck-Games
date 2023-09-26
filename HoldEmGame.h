#pragma once
#include "Game.h"
#include "HoldEmDeck.h"
#include "CardSet.h"

enum class HoldEmState {
    preflop,
    flop,
    turn,
    river,
    undefined
};

class HoldEmGame: public Game {
    protected:
        HoldEmState state;
        HoldEmDeck holdEmDeck;
        std::vector< CardSet<HoldEmRank, Suit> > holdEmHands;
        CardSet<HoldEmRank, Suit> board;
        virtual void deal();
    public:
        HoldEmGame(int argc, const char * argv[]);
        virtual int play();
};