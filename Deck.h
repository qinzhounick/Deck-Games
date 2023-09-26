#pragma once
#include "CardSet.h"
#include <random>
#include <algorithm>


using namespace std;

template<typename R, typename S>
class Deck: public CardSet<R, S> {
    public:
        void shuffle();
        void collect(CardSet<R, S> & col);
};

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE
#include "Deck.cpp"
#endif