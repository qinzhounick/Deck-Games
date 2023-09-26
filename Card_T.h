#pragma once
#include "Suit.h"

template <typename R, typename S>
struct Card {
    R _rank;
    S _suit;
    public:
        Card(R rank, S suit): _rank(rank), _suit(suit) {}
};


template <typename R, typename S>
ostream & operator<< (ostream& os, const Card<R,S>& card);

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE
#include "Card_T.cpp"
#endif