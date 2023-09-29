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