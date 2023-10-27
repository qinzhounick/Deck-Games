//File Name: Card_T.cpp
//Authors: Qinzhou(Nick) Song, Xinyu(Jack) Li
//Email: qinzhounick@wustl.edu, l.xinyujack@wustl.edu
//Summary: source file for Card
//  define operator<<

#include "Card_T.h"

using namespace std;
//define operator<<
template <typename R, typename S>
ostream & operator<< (ostream& os, const Card<R,S>& card) {
    os << card._rank << card._suit; //passing rank and suit to ostream
    return os;
}

// a bool function to compare the ranks of two cards
template <typename R, typename S>
bool checkRank (const Card<R,S> & card_1, const Card<R,S> & card_2){
    if(card_1._rank < card_2._rank || (card_1._rank == card_2._rank && card_1._suit < card_2._suit)) return true;
    else return false;

}

// a bool function to compare the suits of two cards
template <typename R, typename S>
bool checkSuit (const Card<R,S> & card_1, const Card<R,S> & card_2){
    if(card_1._suit < card_2._suit || (card_1._suit == card_2._suit && card_1._rank < card_2._rank)) return true;
    else return false;
}

// define operator< which calls checkRank on two cards, mainly used for sort function
template <typename R, typename S>
bool operator< (const Card<R,S> & card_1, const Card<R,S> & card_2){
    return checkRank(card_1, card_2);
}

// define operator==
template <typename R, typename S>
bool operator== (const Card<R,S> & card_1, const Card<R,S> & card_2){
    return (card_1._rank==card_2._rank && card_1._suit==card_2._suit);
}

