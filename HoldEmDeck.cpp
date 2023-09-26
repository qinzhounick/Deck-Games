//Summary: Define the "shift" operator and prefix increment operator, in the constructor, push back the card once,
//          and print the deck following the setup rule, with each row four cards(four suits).

#include "HoldEmDeck.h"

ostream & operator<< (ostream& os, const HoldEmRank& h) {

    if(h==HoldEmRank::two){
        string output = "2";
        os << output;
    }else if(h==HoldEmRank::three){
        string output = "3";
        os << output;
    }else if(h==HoldEmRank::four){
        string output = "4";
        os << output;
    }else if(h==HoldEmRank::five){
        string output = "5";
        os << output;
    }else if(h==HoldEmRank::six){
        string output = "6";
        os << output;
    }else if(h==HoldEmRank::seven){
        string output = "7";
        os << output;
    }else if(h==HoldEmRank::eight){
        string output = "8";
        os << output;
    }else if(h==HoldEmRank::nine){
        string output = "9";
        os << output;
    }else if(h==HoldEmRank::ten){
        string output = "10";
        os << output;
    }else if(h==HoldEmRank::jack){
        string output = "J";
        os << output;
    }else if(h==HoldEmRank::queen){
        string output = "Q";
        os << output;
    }else if(h==HoldEmRank::king){
        string output = "K";
        os << output;
    }else if(h==HoldEmRank::ace){
        string output = "A";
        os << output;
    }else if(h==HoldEmRank::undefined){
        string output = "?";
        os << output;
    }

    return os;
}

HoldEmRank & operator++ (HoldEmRank& h) {
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

//template<typename r, typename s>
HoldEmDeck::HoldEmDeck() {
    for (HoldEmRank rank = HoldEmRank::two; rank <= HoldEmRank::ace; ++rank) {
        for (Suit suit = Suit::clubs; suit <= Suit::spades; ++suit) {
            CardSet::cards.push_back(Card<HoldEmRank, Suit>(rank, suit));
        }
    }
}
