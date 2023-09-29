//File Name: PinochleGame.h
//Authors: Qinzhou(Nick) Song, Xinyu(Jack) Li
//Email: qinzhounick@wustl.edu, l.xinyujack@wustl.edu
//Summary: header file for PinochleGame
//  declared PinochleGame class

#pragma once
#include "Game.h"
#include "PinochleDeck.h"
#include "CardSet.h"


//PinochleGame class derived from Game base class
class PinochleGame: public Game{
    protected:
        PinochleDeck pinochleDeck;  //declare pinochleDeck variable to hold the deck
        std::vector< CardSet<PinochleRank, Suit> > pinochleHands;  //declare pinochleHand variable to hold player hands
        virtual void deal();  //declare deal function to deal cards to players
    public:
        PinochleGame(int argc, const char * argv[]);  //declare constructor
        virtual int play();  //declare play function to play Pinochle game
};