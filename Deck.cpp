//File Name: Deck.cpp
//Authors: Qinzhou(Nick) Song, Xinyu(Jack) Li
//Email: qinzhounick@wustl.edu, l.xinyujack@wustl.edu
//Summary: source file for Deck
//  define shuffle and collect

#include "Deck.h"

using namespace std;

//define shuffle function with functions 
//  from random and algorithm library
template<typename rank, typename suit>
void Deck<rank, suit>::shuffle() {
    std::random_device device;
    std::mt19937 g(device());

    std::shuffle(CardSet<rank,suit>::cards.begin(), CardSet<rank,suit>::cards.end(), g);
}

//define collect function
template<typename rank, typename suit>
void Deck<rank, suit>::collect(CardSet<rank, suit> & col) {
    if(col.is_empty()) { //check if the Card passed in is empty
        throw std::runtime_error("runtime error"); //throw runtime error if empty
    } else {
        while(!col.is_empty()){ //else pass all the cards into deck
            col >> *this;
        }
    }
}