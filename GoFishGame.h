//File Name: GoFishGame.h
//Authors: Qinzhou(Nick) Song, Xinyu(Jack) Li
//Email: qinzhounick@wustl.edu, l.xinyujack@wustl.edu
//Summary: header file for GoFishGame
//  declared HoldEmState enum, HoldEmGame class, HoldEmHandRank enum class, and operator<<

#pragma once
#include "Game.h"
#include "Suit.h"
#include "HoldEmDeck.h"

template <typename s=Suit, typename r=HoldEmRank, typename d=HoldEmDeck>
class GoFishGame: public Game{
    public:
        GoFishGame(int argc, char * argv);
        virtual ~GoFishGame();
        virtual int play();  //declare play function to play Pinochle game
    protected:
        d goFishDeck;
        std::vector< CardSet<r, s> > goFishHands;
        std::vector< CardSet<r, s> > goFishBooks;
        virtual void deal();
};

template <typename s=Suit, typename r=PinochleRank, typename d=HoldEmDeck>
class GoFishGame: public Game{
    public:
        GoFishGame(int argc, char * argv);
        virtual ~GoFishGame();
        virtual int play();  //declare play function to play Pinochle game
    protected:
        d goFishDeck;
        std::vector< CardSet<r, s> > goFishHands;
        std::vector< CardSet<r, s> > goFishBooks;
        virtual void deal();
};

template <typename s=Suit, typename r=UnoRank, typename d=HoldEmDeck>
class GoFishGame: public Game{
    public:
        GoFishGame(int argc, char * argv);
        virtual ~GoFishGame();
        virtual int play();  //declare play function to play Pinochle game
    protected:
        d goFishDeck;
        std::vector< CardSet<r, s> > goFishHands;
        std::vector< CardSet<r, s> > goFishBooks;
        virtual void deal();
};

//inclusion guard
#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE
#include "GoFishGame.cpp"
#endif