#pragma once
#include <iostream>
#include "Card_T.h"
#include <vector>

using namespace std;

template <typename R, typename S>
class CardSet {
    protected:
        vector< Card<R, S> > cards;
    public:
        CardSet<R,S> & operator>> (CardSet<R,S> & c);
        void print(ostream& os, size_t size);
        bool is_empty();

};

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE
#include "CardSet.cpp"
#endif