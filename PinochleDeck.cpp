//File Name: PinochleDeck.cpp
//Authors: Qinzhou(Nick) Song, Xinyu(Jack) Li
//Email: qinzhounick@wustl.edu, l.xinyujack@wustl.edu
//Summary: Source file for PinochleDeck
//  Define the "shift" operator and prefix increment operator, in the constructor, push back the card twice
//  Define printRank and getRank helper functions for correct type comparison

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

// print PinochleRank
// helper function to print out the rank so we can get the string and compare with the input rank
std::string printRank(PinochleRank r){
    if(r==PinochleRank::nine){
        return "9";
    }else if(r==PinochleRank::jack){
        return "J";
    }else if(r==PinochleRank::queen){
        return "Q";
    }else if(r==PinochleRank::king){
        return "K";
    }else if(r==PinochleRank::ten){
        return "10";
    }else if(r==PinochleRank::ace){
        return "A";
    }

    return "?";
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

// helper function to get the string of the rank and return the "rank" type of the input rank for comparison
PinochleRank PinochleDeck::getRank(std::string & s){
    if(s=="9"){
        return PinochleRank::nine;
    }else if(s=="J"){
        return PinochleRank::jack;
    }else if(s=="Q"){
        return PinochleRank::queen;
    }else if(s=="K"){
        return PinochleRank::king;
    }else if(s=="10"){
        return PinochleRank::ten;
    }else if(s=="A"){
        return PinochleRank::ace;
    }
        
    return PinochleRank::undefined;

}