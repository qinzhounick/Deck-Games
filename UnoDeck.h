#pragma once

#include "Deck.h"
#include "UnoColor.h"

enum class UnoRank {
    zero,
    one,
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    skip,
    reverse,
    drawtwo,
    drawfour,
    wild,
    blank,
    undefined
};


class UnoDeck: public Deck<UnoRank, Color>{
    public:
        UnoDeck();  //default constructor
};


std::ostream & operator<< (std::ostream& os, const UnoRank& r);
UnoRank & operator++ (UnoRank& r);
std::string printRank(UnoRank r);