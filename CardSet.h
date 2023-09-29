//File Name: CardSet.h
//Authors: Qinzhou(Nick) Song, Xinyu(Jack) Li
//Email: qinzhounick@wustl.edu, l.xinyujack@wustl.edu
//Summary: header file for CardSet
//  declare base class CardSet
#pragma once
#include "Card_T.h"

using namespace std;

//base template class CardSet
template <typename R, typename S>
class CardSet {
    protected:
        //vector cards to hold Card type objects
        std::vector< Card<R, S> > cards;
    public:
        //overloaded shift operator
        CardSet<R,S> & operator>> (CardSet<R,S> & c);
        //print function to print cards in vector cards
        void print(ostream& os, size_t size);
        //is_empty function to check if vector cards is empty
        bool is_empty();

};

//inclusion guard
#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE
#include "CardSet.cpp"
#endif