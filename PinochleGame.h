//File Name: PinochleGame.h
//Authors: Qinzhou(Nick) Song, Xinyu(Jack) Li
//Email: qinzhounick@wustl.edu, l.xinyujack@wustl.edu
//Summary: header file for PinochleGame
//  declared PinochleGame class

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

const int PINOCHLE_PRINT = 12;
//PinochleGame class derived from Game base class
class PinochleGame: public Game{
    private:
        void suit_independent_evaluation(const CardSet<PinochleRank,Suit> cardSet, vector<PinochleMelds> & pms);
    protected:
        PinochleDeck pinochleDeck;  //declare pinochleDeck variable to hold the deck
        std::vector< CardSet<PinochleRank, Suit> > pinochleHands;  //declare pinochleHand variable to hold player hands
        virtual void deal();  //declare deal function to deal cards to players
    public:
        PinochleGame(int argc, const char * argv[]);  //declare constructor
        virtual int play();  //declare play function to play Pinochle game
        static std::unordered_map<char*, int> Points= {
            {"dix",10}, {"offsuitmarriage",20},{"fortyjacks", 40}, {"pinochle", 40}, 
            {"insuitmarriage",40}, {"sixtyqueens", 60}, {"eightykings", 80}, {"hundredaces", 100}, 
            {"insuitrun", 150}, {"doublepinochle", 300}, {"fourhundredjacks", 400}, {"sixhundredqueens", 600}, 
            {"eighthundredkings", 600}, {"thousandaces", 1000}, {"insuitdoublerun", 1500}
        };
};

//left shift operator
std::ostream & operator<< (std::ostream& os, const PinochleMelds & pm);