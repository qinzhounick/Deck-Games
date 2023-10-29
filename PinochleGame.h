//File Name: PinochleGame.h
//Authors: Qinzhou(Nick) Song, Xinyu(Jack) Li
//Email: qinzhounick@wustl.edu, l.xinyujack@wustl.edu
//Summary: header file for PinochleGame
//  declared PinochleGame class, PinochleMelds enum class, and operator<<

#pragma once
#include "Game.h"
#include "PinochleDeck.h"
#include "CardSet.h"

enum class PinochleMelds{
    dix, 
    offsuitmarriage,
    fortyjacks, 
    pinochle, 
    insuitmarriage, 
    sixtyqueens, 
    eightykings, 
    hundredaces, 
    insuitrun, 
    doublepinochle, 
    fourhundredjacks, 
    sixhundredqueens, 
    eighthundredkings, 
    thousandaces, 
    insuitdoublerun
};

const int ENUM_MELDS_INDEX = 15;
const int PINOCHLE_PRINT = 12;
//PinochleGame class derived from Game base class
class PinochleGame: public Game{
    private:
        void suit_independent_evaluation(const CardSet<PinochleRank,Suit> & cardSet, vector<PinochleMelds> & melds);
    protected:
        PinochleDeck pinochleDeck;  //declare pinochleDeck variable to hold the deck
        std::vector< CardSet<PinochleRank, Suit> > pinochleHands;  //declare pinochleHand variable to hold player hands
        virtual void deal();  //declare deal function to deal cards to players
    public:
        PinochleGame(int argc, const char * argv[]);  //declare constructor
        virtual int play();  //declare play function to play Pinochle game
        static std::vector<std::pair<std::string, int> > points;  //vector to store meld strings and points

};

//left shift operator
std::ostream & operator<< (std::ostream& os, const PinochleMelds & pm);

