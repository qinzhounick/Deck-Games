//File Name: PinochleDeck.cpp
//Authors: Qinzhou(Nick) Song, Xinyu(Jack) Li
//Email: qinzhounick@wustl.edu, l.xinyujack@wustl.edu
//Summary: Source file for PinochleDeck
//  Define the "shift" operator and prefix increment operator, in the constructor, push back the card twice,
//  and print the deck following the setup rule, with each row eight cards(four suits*2).

#include "PinochleDeck.h"

using namespace std;

//shift operator<< for Pinochle ranks
std::ostream & operator<< (std::ostream& os, const PinochleRank& r) {
    //output all ranks
    if(r==PinochleRank::nine){
        os <<  "9";
    }else if(r==PinochleRank::jack){
        os <<  "J";
    }else if(r==PinochleRank::queen){
        os <<  "Q";
    }else if(r==PinochleRank::king){
        os <<  "K";
    }else if(r==PinochleRank::ten){
        os <<  "10";
    }else if(r==PinochleRank::ace){
        os <<  "A";
    }else if(r==PinochleRank::undefined){
        os <<  "?";
    }

    return os;
}

//prefix increment operator++ for Pinochle
PinochleRank & operator++ (PinochleRank & r){
    //switch statement to move to the next rank
    switch(r) {
        case PinochleRank::nine:
            r = PinochleRank::jack;
            break;
        case PinochleRank::jack:
            r = PinochleRank::queen;
            break;
        case PinochleRank::queen:
            r = PinochleRank::king;
            break;
        case PinochleRank::king:
            r = PinochleRank::ten;
            break;
        case PinochleRank::ten:
            r = PinochleRank::ace;
            break;
        case PinochleRank::ace:
            r = PinochleRank::undefined;
            break;
        case PinochleRank::undefined:
            break;
    }

    return r;
}

//default constructor
PinochleDeck::PinochleDeck(){
    for (PinochleRank rank = PinochleRank::nine; rank <= PinochleRank::ace; ++rank) { //loop through rank
        for (Suit suit = Suit::clubs; suit <= Suit::spades; ++suit) { //loop through suit
            cards.push_back(Card<PinochleRank, Suit>(rank, suit));
            cards.push_back(Card<PinochleRank, Suit>(rank, suit)); //push twice
        }
    }
}