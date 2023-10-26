//File Name: HoldEmGame.h
//Authors: Qinzhou(Nick) Song, Xinyu(Jack) Li
//Email: qinzhounick@wustl.edu, l.xinyujack@wustl.edu
//Summary: header file for HoldEmGame
//  declared HoldEmState enum and HoldEmGame class 

#pragma once
#include "Game.h"
#include "HoldEmDeck.h"
#include "CardSet.h"


enum class HoldEmHandRank{
    xhigh, 
    pair, 
    twopair, 
    threeofakind, 
    straight, 
    flush, 
    fullhouse, 
    fourofakind, 
    straightflush, 
    undefined
};

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
        struct playerStruct{
            CardSet<HoldEmRank, Suit> _cardset;
            std::string _name;
            HoldEmHandRank _rank;
            playerStruct(CardSet<HoldEmRank, Suit> cardset, std::string name, HoldEmHandRank rank);
        };
    private:
        HoldEmHandRank holdem_hand_evaluation(const CardSet<HoldEmRank, Suit> & playerHand);
};


//left shift operator
std::ostream & operator<< (std::ostream& os, const HoldEmHandRank & hhr);
//less than operator
bool operator< (const HoldEmGame::playerStruct & player1, const HoldEmGame::playerStruct & player2);

//helper function for one pair rank
bool pair_helper(vector<Card<HoldEmRank, Suit> > player1Cards, vector<Card<HoldEmRank, Suit> > player2Cards);
//helper function for two pair rank
bool twopair_helper(vector<Card<HoldEmRank, Suit> > player1Cards, vector<Card<HoldEmRank, Suit> > player2Cards);
//helper function for three of a kind and full house rank
bool threeofakindOrFullhouse_helper(vector<Card<HoldEmRank, Suit> > player1Cards, vector<Card<HoldEmRank, Suit> > player2Cards);
//helper function for straight rank
bool straight_helper(vector<Card<HoldEmRank, Suit> > player1Cards, vector<Card<HoldEmRank, Suit> > player2Cards);
//helper function for flush or xhigh rank
bool flushOrXhigh_helper(vector<Card<HoldEmRank, Suit> > player1Cards, vector<Card<HoldEmRank, Suit> > player2Cards);
//helper function for four of a kind rank
bool fourofakind_helper(vector<Card<HoldEmRank, Suit> > player1Cards, vector<Card<HoldEmRank, Suit> > player2Cards);
//helper function for straight flush rank
bool straightflush_helper(vector<Card<HoldEmRank, Suit> > player1Cards, vector<Card<HoldEmRank, Suit> > player2Cards);