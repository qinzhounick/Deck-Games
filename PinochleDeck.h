//File Name: PinochleDeck.h
//Authors: Qinzhou(Nick) Song, Xinyu(Jack) Li
//Email: qinzhounick@wustl.edu, l.xinyujack@wustl.edu
//Summary: Header file for PinochleDeck
//  declare the rank for Pinochle deck, override the "shift" operator and prefix increment operator,
//  declare the derived class(from Deck) of Pinochle deck, and a public constructor.

#pragma once
#include "Deck.h"
#include "Suit.h"

//declare enum for PinochleRank
enum class PinochleRank {
    nine = 0,
    jack = 1,
    queen = 2,
    king = 3, 
    ten = 4,
    ace = 5,
    undefined = 6
};


//declare prefix operator++ and operator<<
std::ostream & operator<< (std::ostream& os, const PinochleRank& r);
PinochleRank & operator++ (PinochleRank& r);
std::string printRank(PinochleRank r);


class PinochleDeck: public Deck<PinochleRank, Suit>{
    public:
        PinochleDeck();  //default constructor
        PinochleRank getRank(std::string & s);
};