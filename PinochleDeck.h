//Summary: Declare the rank for Pinochle deck, override the "shift" operator and prefix increment operator,
//          declare the deriived class of Pinochle deck, with a private vector of Pinochle cards, a public
//          constructor and overloaded print method.

#pragma once
#include <vector>
#include <string>
#include "Deck.h"
#include "Card_T.h"

enum class PinochleRank {
    nine = 0,
    jack = 1,
    queen = 2,
    king = 3, 
    ten = 4,
    ace = 5,
    undefined = 6
};

const int PINOCHLE_ROW_SIZE = 8;
const int PINOCHLE_OFFSET = 7;

ostream & operator<< (ostream& os, const PinochleRank& r);

PinochleRank & operator++ (PinochleRank& r);

class PinochleDeck: public Deck<PinochleRank, Suit>{
    public:
        PinochleDeck();
};