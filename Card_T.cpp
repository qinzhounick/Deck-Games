#include "Card_T.h"

template <typename R, typename S>
ostream & operator<< (ostream& os, const Card<R,S>& card) {
    os << card._rank << card._suit;
    return os;
}