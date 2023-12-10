//File Name: GoFishGame.h
//Authors: Qinzhou(Nick) Song, Xinyu(Jack) Li
//Email: qinzhounick@wustl.edu, l.xinyujack@wustl.edu
//Summary: header file for GoFishGame
//  define constructor and functions

#pragma once
#include "Game.h"
#include "Suit.h"
#include "HoldEmDeck.h"
#include "PinochleDeck.h"
#include "UnoDeck.h"

// GoFishGame constructor
template <typename r=HoldEmRank, typename s=Suit, typename d=HoldEmDeck>
class GoFishGame: public Game{
    public:
        GoFishGame(int argc, const char * argv[]);
        virtual ~GoFishGame(){}; // virtual destructor
        virtual int play();  //declare play function to play Pinochle game
        static_assert(std::is_base_of<CardSet<r,s>, d>::value == true, "Deck does not use the given rank and suit");
        bool collect_books(int playerNumber); // collect the books if there are 4 of kind in the hand
    protected:
        std::string deckType; // get the type of the deck for rule checking
        d goFishDeck;  // the deck of the GoFish game
        std::vector< CardSet<r, s> > goFishHands;   // player's hand
        std::vector< CardSet<r, s> > goFishBooks;   // player's books
        std::vector<std::pair<std::string,int> > goFishScores;
        std::vector<int> invalidPlayers;  // vector to store player that are out of game
        virtual void deal(); // deal card to player
        bool turn(int playerNumber);  // turn function for each turn of the current player
};

//inclusion guard
#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE
#include "GoFishGame.cpp"
#endif