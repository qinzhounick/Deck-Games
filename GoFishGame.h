//File Name: GoFishGame.h
//Authors: Qinzhou(Nick) Song, Xinyu(Jack) Li
//Email: qinzhounick@wustl.edu, l.xinyujack@wustl.edu
//Summary: header file for GoFishGame
//  declared HoldEmState enum, HoldEmGame class, HoldEmHandRank enum class, and operator<<

#pragma once
#include "Game.h"
#include "Suit.h"
#include "HoldEmDeck.h"
#include "PinochleDeck.h"
#include "UnoDeck.h"


template <typename r=HoldEmRank, typename s=Suit, typename d=HoldEmDeck>
class GoFishGame: public Game{
    public:
        GoFishGame(int argc, const char * argv[]);
        virtual ~GoFishGame(){};
        virtual int play();  //declare play function to play Pinochle game
        static_assert(std::is_base_of<CardSet<r,s>, d>::value == true, "Deck does not use the given rank and suit");
        bool collect_books(int playerNumber);
    protected:
        std::string deckType;
        d goFishDeck;
        std::vector< CardSet<r, s> > goFishHands;
        std::vector< CardSet<r, s> > goFishBooks;
        std::vector<std::pair<std::string,int> > goFishScores;
        std::vector<int> invalidPlayers;
        virtual void deal();
        bool turn(int playerNumber);
};

//inclusion guard
#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE
#include "GoFishGame.cpp"
#endif