//File Name: HoldEmGame.h
//Authors: Qinzhou(Nick) Song, Xinyu(Jack) Li
//Email: qinzhounick@wustl.edu, l.xinyujack@wustl.edu
//Summary: header file for HoldEmGame
//  declared HoldEmState enum and HoldEmGame class 

#pragma once
#include "Game.h"
#include "HoldEmDeck.h"
#include "CardSet.h"

//HoldEmState enum to hold different states of HoldEm
enum class HoldEmState {
    preflop,
    flop,
    turn,
    river,
    undefined
};

//HoldEmGame class derived from Game base class
class HoldEmGame: public Game {
    protected:
        HoldEmState state;  //declare state variable to hold the current state
        HoldEmDeck holdEmDeck;  //declare holdEmDeck variable to hold the deck
        std::vector< CardSet<HoldEmRank, Suit> > holdEmHands;  //declare holdEmHand variable to hold player hands
        CardSet<HoldEmRank, Suit> board;  //declare board variable to hold the current board
        virtual void deal();  //declare deal function to deal cards to players
    public:
        HoldEmGame(int argc, const char * argv[]);  //declare constructor
        virtual int play();  //declare play function to play HoldEm game
};