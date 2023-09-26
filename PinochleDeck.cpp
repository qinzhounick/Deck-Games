//Summary: Define the "shift" operator and prefix increment operator, in the constructor, push back the card twice,
//          and print the deck following the setup rule, with each row eight cards(four suits).

#include "PinochleDeck.h"

ostream & operator<< (ostream& os, const PinochleRank& r) {
    if(r==PinochleRank::nine){
        string output = "9";
        os << output;
    }else if(r==PinochleRank::jack){
        string output = "J";
        os << output;
    }else if(r==PinochleRank::queen){
        string output = "Q";
        os << output;
    }else if(r==PinochleRank::king){
        string output = "K";
        os << output;
    }else if(r==PinochleRank::ten){
        string output = "10";
        os << output;
    }else if(r==PinochleRank::ace){
        string output = "A";
        os << output;
    }else if(r==PinochleRank::undefined){
        string output = "?";
        os << output;
    }

    return os;
}

PinochleRank & operator++ (PinochleRank & r){
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

//template<typename r, typename s>
PinochleDeck::PinochleDeck() {
    for (PinochleRank rank = PinochleRank::nine; rank <= PinochleRank::ace; ++rank) {
        for (Suit suit = Suit::clubs; suit <= Suit::spades; ++suit) {
            CardSet::cards.push_back(Card<PinochleRank, Suit>(rank, suit));
            CardSet::cards.push_back(Card<PinochleRank, Suit>(rank, suit));
        }
    }
}