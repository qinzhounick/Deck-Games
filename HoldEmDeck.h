//Summary: Declare the rank for HoldEm deck, override the "shift" operator and prefix increment operator,
//          declare the deriived class of HoldEm deck, with a private vector of HoldEm cards, a public
//          constructor and overloaded print method.

#pragma once
#include <vector>
#include <string>
#include "Deck.h"
#include "Card_T.h"

enum class HoldEmRank {
    two = 0,
    three = 1,
    four = 2,
    five = 3,
    six = 4,
    seven = 5,
    eight = 6,
    nine = 7,
    ten = 8,
    jack = 9,
    queen = 10,
    king = 11, 
    ace = 12,
    undefined = 13
};

const int HOLDEM_ROW_SIZE = 4;
const int HOLDEM_OFFSET = 3;

ostream & operator<< (ostream& os, const HoldEmRank& h);

HoldEmRank & operator++ (HoldEmRank& h);

class HoldEmDeck: public Deck<HoldEmRank, Suit>{
    public:
        HoldEmDeck();
};