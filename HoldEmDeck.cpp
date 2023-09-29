//File Name: HoldEmDeck.cpp
//Authors: Qinzhou(Nick) Song, Xinyu(Jack) Li
//Email: qinzhounick@wustl.edu, l.xinyujack@wustl.edu
//Summary: Source file for HoldEmDeck
//  define the "shift" operator and prefix increment operator, in the constructor, push back the card once

#include "HoldEmDeck.h"

using namespace std;

//define operator<< for HoldEmRank
ostream & operator<< (ostream& os, const HoldEmRank& h) {
    //output all the ranks
    if(h==HoldEmRank::two){
        os <<  "2";
    }else if(h==HoldEmRank::three){
        os <<  "3";
    }else if(h==HoldEmRank::four){
        os <<  "4";
    }else if(h==HoldEmRank::five){
        os <<  "5";
    }else if(h==HoldEmRank::six){
        os <<  "6";
    }else if(h==HoldEmRank::seven){
        os <<  "7";
    }else if(h==HoldEmRank::eight){
        os <<  "8";
    }else if(h==HoldEmRank::nine){
        os <<  "9";
    }else if(h==HoldEmRank::ten){
        os <<  "10";
    }else if(h==HoldEmRank::jack){
        os <<  "J";
    }else if(h==HoldEmRank::queen){
        os <<  "Q";
    }else if(h==HoldEmRank::king){
        os <<  "K";
    }else if(h==HoldEmRank::ace){
        os <<  "A";
    }else if(h==HoldEmRank::undefined){
        os <<  "?";
    }
    return os;
}

//define prefix increment operator for HoldEm
HoldEmRank & operator++ (HoldEmRank& h) {
    //switch statement to change to the next rank
    switch(h) {
        case HoldEmRank::two:
            h = HoldEmRank::three;
            break;
        case HoldEmRank::three:
            h = HoldEmRank::four;
            break;
        case HoldEmRank::four:
            h = HoldEmRank::five;
            break;
        case HoldEmRank::five:
            h = HoldEmRank::six;
            break;
        case HoldEmRank::six:
            h = HoldEmRank::seven;
            break;
        case HoldEmRank::seven:
            h = HoldEmRank::eight;
            break;
        case HoldEmRank::eight:
            h = HoldEmRank::nine;
            break;
        case HoldEmRank::nine:
            h = HoldEmRank::ten;
            break;
        case HoldEmRank::ten:
            h = HoldEmRank::jack;
            break;
        case HoldEmRank::jack:
            h = HoldEmRank::queen;
            break;
        case HoldEmRank::queen:
            h = HoldEmRank::king;
            break;
        case HoldEmRank::king:
            h = HoldEmRank::ace;
            break;
        case HoldEmRank::ace:
            h = HoldEmRank::undefined;
            break;
        case HoldEmRank::undefined:
            break;
    }
    return h;
}

//Default constructor for HoldEmDeck
HoldEmDeck::HoldEmDeck() {
    for (HoldEmRank rank = HoldEmRank::two; rank <= HoldEmRank::ace; ++rank) { //loop through HoldEm ranks
        for (Suit suit = Suit::clubs; suit <= Suit::spades; ++suit) { //loop through suit
            CardSet::cards.push_back(Card<HoldEmRank, Suit>(rank, suit)); //push back the card into vector
        }
    }
}
