//File Name: UnoDeck.h
//Authors: Qinzhou(Nick) Song, Xinyu(Jack) Li
//Email: qinzhounick@wustl.edu, l.xinyujack@wustl.edu
//Summary: Header file for UnoDeck
//  declare the rank for Uno deck, override the "shift" operator and prefix increment operator,
//  declare the derived class(from Deck) of Uno deck, and a public constructor.
//  declare printRank and getRank helper functions for correct type comparison

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
        UnoRank getRank(std::string & s);
};


std::ostream & operator<< (std::ostream& os, const UnoRank& r);
UnoRank & operator++ (UnoRank& r);
std::string printRank(UnoRank r);
