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
        GoFishGame(int argc, char * argv);
        virtual ~GoFishGame();
        virtual int play();  //declare play function to play Pinochle game
        static_assert(std::is_base_of<CardSet<s,r>, d>::value == true, "Deck does not use the given rank and suit");
        bool collect_books(int playerNumber);
    protected:
        d goFishDeck;
        std::vector< CardSet<r, s> > goFishHands;
        std::vector< CardSet<r, s> > goFishBooks;
        virtual void deal();
        bool turn(int playerNumber);
};

//-----------------------------------------------Class Template Specializations-----------------------------------------------------
template <>
class GoFishGame<Suit, HoldEmRank, HoldEmDeck>: public Game{
    public:
        GoFishGame(int argc, char * argv);
        virtual ~GoFishGame();
        virtual int play();  //declare play function to play Pinochle game
        bool collect_books(int playerNumber);
    protected:
        HoldEmDeck goFishDeck;
        std::vector< CardSet<HoldEmRank, Suit> > goFishHands;
        std::vector< CardSet<HoldEmRank, Suit> > goFishBooks;
        virtual void deal();
        bool turn(int playerNumber);
};

template <>
class GoFishGame<Suit, PinochleRank, HoldEmDeck>: public Game{
    public:
        GoFishGame(int argc, char * argv);
        virtual ~GoFishGame();
        virtual int play();  //declare play function to play Pinochle game
        bool collect_books(int playerNumber);
    protected:
        HoldEmDeck goFishDeck;
        std::vector< CardSet<PinochleRank, Suit> > goFishHands;
        std::vector< CardSet<PinochleRank, Suit> > goFishBooks;
        virtual void deal();
        bool turn(int playerNumber);
};

template <>
class GoFishGame<Suit, HoldEmRank, PinochleDeck>: public Game{
    public:
        GoFishGame(int argc, char * argv);
        virtual ~GoFishGame();
        virtual int play();  //declare play function to play Pinochle game
        bool collect_books(int playerNumber);
    protected:
        PinochleDeck goFishDeck;
        std::vector< CardSet<HoldEmRank, Suit> > goFishHands;
        std::vector< CardSet<HoldEmRank, Suit> > goFishBooks;
        virtual void deal();
        bool turn(int playerNumber);
};

template <>
class GoFishGame<Suit, PinochleRank, PinochleDeck>: public Game{
    public:
        GoFishGame(int argc, char * argv);
        virtual ~GoFishGame();
        virtual int play();  //declare play function to play Pinochle game
        bool collect_books(int playerNumber);
    protected:
        PinochleDeck goFishDeck;
        std::vector< CardSet<PinochleRank, Suit> > goFishHands;
        std::vector< CardSet<PinochleRank, Suit> > goFishBooks;
        virtual void deal();
        bool turn(int playerNumber);
};

template <>
class GoFishGame<Color, UnoRank, UnoDeck>: public Game{
    public:
        GoFishGame(int argc, char * argv);
        virtual ~GoFishGame();
        virtual int play();  //declare play function to play Pinochle game
        bool collect_books(int playerNumber);
    protected:
        UnoDeck goFishDeck;
        std::vector< CardSet<UnoRank, Color> > goFishHands;
        std::vector< CardSet<UnoRank, Color> > goFishBooks;
        virtual void deal();
        bool turn(int playerNumber);
};

//inclusion guard
#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE
#include "GoFishGame.cpp"
#endif