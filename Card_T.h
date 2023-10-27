//File Name: Card_T.h
//Authors: Qinzhou(Nick) Song, Xinyu(Jack) Li
//Email: qinzhounick@wustl.edu, l.xinyujack@wustl.edu
//Summary: header file for Card
//  declare struct card, operator<<, checkRank, checkSuit, operator<, operator==

#pragma once
#include "Suit.h"

//declaration of template struct Card
template <typename R, typename S>
struct Card {
    public:
        //member variables
        R _rank;
        S _suit;

        //constructor
        Card(R rank, S suit): _rank(rank), _suit(suit) {}
};

//template shift operator for struct card
template <typename R, typename S>
std::ostream & operator<< (std::ostream& os, const Card<R,S>& card);

template <typename R, typename S>
bool checkRank(const Card<R,S> & card_1, const Card<R,S> & card_2);

template <typename R, typename S>
bool checkSuit(const Card<R,S> & card_1, const Card<R,S> & card_2);

template <typename R, typename S>
bool operator< (const Card<R,S> & card_1, const Card<R,S> & card_2);

template <typename R, typename S>
bool operator== (const Card<R,S> & card_1, const Card<R,S> & card_2);

//inclusion guard
#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE
#include "Card_T.cpp"
#endif