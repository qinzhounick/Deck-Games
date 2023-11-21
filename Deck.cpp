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