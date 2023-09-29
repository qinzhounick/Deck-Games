//File Name: Deck.h
//Authors: Qinzhou(Nick) Song, Xinyu(Jack) Li
//Email: qinzhounick@wustl.edu, l.xinyujack@wustl.edu
//Summary: header file for Deck
//  declare derived class from base class CardSet


#pragma once
#include "CardSet.h"
#include <random>
#include <algorithm>


//derived class deck
template<typename R, typename S>
class Deck: public CardSet<R, S> {
    public:
        void shuffle(); //shuffle the cards in deck
        void collect(CardSet<R, S> & col); //collect cards from CardSet back to deck
};


//inclusion guard
#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE
#include "Deck.cpp"
#endif