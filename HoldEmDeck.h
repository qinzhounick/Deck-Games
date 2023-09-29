//File Name: HoldEmDeck.h
//Authors: Qinzhou(Nick) Song, Xinyu(Jack) Li
//Email: qinzhounick@wustl.edu, l.xinyujack@wustl.edu
//Summary: Header file for HoldEmDeck
//  declare the rank for HoldEm deck, override the "shift" operator and prefix increment operator,
//  declare the deriived class(from Deck) of HoldEm deck, and a public constructor.

#pragma once
#include "Deck.h"
#include "Card_T.h"

//const int variable to avoid magic number
const int FLOP_PRINT = 3;  //flop print size
const int TURN_PRINT = 4;  //turn print size
const int RIVER_PRINT = 5;  //river print size 



//declare enum for HoldEm ranks
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

//decalre prefix increment operator and operator<<
std::ostream & operator<< (std::ostream& os, const HoldEmRank& h);
HoldEmRank & operator++ (HoldEmRank& h);

//declare HoldEmDeck class that inherits from Deck
class HoldEmDeck: public Deck<HoldEmRank, Suit>{
    public:
        HoldEmDeck(); //default constuctor
};