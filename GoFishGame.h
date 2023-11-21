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

template <typename s, typename r, typename d>
class GoFishGame: public Game{
    public:
        GoFishGame(int argc, char * argv){};
        virtual ~GoFishGame();
        virtual int play();  //declare play function to play Pinochle game
    protected:
        d goFishDeck;
        std::vector< CardSet<r, s> > goFishHands;
        std::vector< CardSet<r, s> > goFishBooks;
        virtual void deal();
};


template <>
class GoFishGame<Suit, HoldEmRank, HoldEmDeck>: public Game{
    public:
        GoFishGame(int argc, char * argv);
        virtual ~GoFishGame();
        virtual int play();  //declare play function to play Pinochle game
    protected:
        HoldEmDeck goFishDeck;
        std::vector< CardSet<HoldEmRank, Suit> > goFishHands;
        std::vector< CardSet<HoldEmRank, Suit> > goFishBooks;
        virtual void deal();
};

template <>
class GoFishGame<Suit, PinochleRank, HoldEmDeck>: public Game{
    public:
        GoFishGame(int argc, char * argv);
        virtual ~GoFishGame();
        virtual int play();  //declare play function to play Pinochle game
    protected:
        HoldEmDeck goFishDeck;
        std::vector< CardSet<PinochleRank, Suit> > goFishHands;
        std::vector< CardSet<PinochleRank, Suit> > goFishBooks;
        virtual void deal();
};

template <>
class GoFishGame<Suit, UnoRank, HoldEmDeck>: public Game{
    public:
        GoFishGame(int argc, char * argv);
        virtual ~GoFishGame();
        virtual int play();  //declare play function to play Pinochle game
    protected:
        HoldEmDeck goFishDeck;
        std::vector< CardSet<UnoRank, Suit> > goFishHands;
        std::vector< CardSet<UnoRank, Suit> > goFishBooks;
        virtual void deal();
};

//inclusion guard
#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE
#include "GoFishGame.cpp"
#endif