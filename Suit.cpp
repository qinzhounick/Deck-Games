#include "Suit.h"

ostream & operator<< (ostream& os, const Suit& s){
    char output;

    if(s==Suit::clubs){
        output='C';
    }else if(s==Suit::diamonds){
        output='D';
    }else if(s==Suit::hearts){
        output='H';
    }else if(s==Suit::spades){
        output='S';
    }else if(s==Suit::undefined){
        output='?';
    }

    os << output;
    return os;
}

Suit & operator++ (Suit& s) {
    switch(s) {
        case Suit::clubs:
            s = Suit::diamonds;
            break;
        case Suit::diamonds:
            s = Suit::hearts;
            break;
        case Suit::hearts:
            s = Suit::spades;
            break;
        case Suit::spades:
            s = Suit::undefined;
            break;
        case Suit::undefined:
            break;
    }
    return s;
}