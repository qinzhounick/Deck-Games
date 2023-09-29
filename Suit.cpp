//File Name: Suit.cpp
//Authors: Qinzhou(Nick) Song, Xinyu(Jack) Li
//Email: qinzhounick@wustl.edu, l.xinyujack@wustl.edu
//Summary: source file for Suit
//  define two overloaded operators

#include "Suit.h"

using namespace std;

//definition for shift operator
ostream & operator<< (ostream& os, const Suit& s){
    char output;

    //output all suit
    if(s==Suit::clubs){
        output = 'C';
    }else if(s==Suit::diamonds){
        output = 'D';
    }else if(s==Suit::hearts){
        output = 'H';
    }else if(s==Suit::spades){
        output = 'S';
    }else if(s==Suit::undefined){
        output = '?';
    }


    os << output;

    return os;
}

//prefix increment operator
Suit & operator++ (Suit& s){

    //switch statement to change to next suit
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