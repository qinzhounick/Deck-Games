#include "UnoDeck.h"

using namespace std;

//shift operator<< for Uno ranks
std::ostream & operator<< (std::ostream& os, const UnoRank& r) {
    //output all ranks
    if(r==UnoRank::zero){
        os <<  "0";
    }else if(r==UnoRank::one){
        os <<  "1";
    }else if(r==UnoRank::two){
        os <<  "2";
    }else if(r==UnoRank::three){
        os <<  "3";
    }else if(r==UnoRank::four){
        os <<  "4";
    }else if(r==UnoRank::five){
        os <<  "5";
    }else if(r==UnoRank::six){
        os <<  "6";
    }else if(r==UnoRank::seven){
        os <<  "7";
    }else if(r==UnoRank::eight){
        os <<  "8";
    }else if(r==UnoRank::nine){
        os <<  "9";
    }else if(r==UnoRank::skip){
        os <<  "Skip";
    }else if(r==UnoRank::reverse){
        os <<  "Reverse";
    }else if(r==UnoRank::drawtwo){
        os <<  "Drawtwo";
    }else if(r==UnoRank::drawfour){
        os <<  "Drawfour";
    }else if(r==UnoRank::wild){
        os <<  "Wild";
    }else if(r==UnoRank::blank){
        os <<  "Blank";
    }else if(r==UnoRank::undefined){
        os <<  "?";
    }

    return os;
}

//prefix increment operator++ for Uno
UnoRank & operator++ (UnoRank& r){
    //switch statement to move to the next rank
    switch(r) {
        case UnoRank::zero:
            r = UnoRank::one;
            break;
        case UnoRank::one:
            r = UnoRank::two;
            break;
        case UnoRank::two:
            r = UnoRank::three;
            break;
        case UnoRank::three:
            r = UnoRank::four;
            break;
        case UnoRank::four:
            r = UnoRank::five;
            break;
        case UnoRank::five:
            r = UnoRank::six;
            break;
        case UnoRank::six:
            r = UnoRank::seven;
            break;
        case UnoRank::seven:
            r = UnoRank::eight;
            break;
        case UnoRank::eight:
            r = UnoRank::nine;
            break;
        case UnoRank::nine:
            r = UnoRank::skip;
            break;
        case UnoRank::skip:
            r = UnoRank::reverse;
            break;
        case UnoRank::reverse:
            r = UnoRank::drawtwo;
            break;
        case UnoRank::drawtwo:
            r = UnoRank::drawfour;
            break;
        case UnoRank::drawfour:
            r = UnoRank::wild;
            break;
        case UnoRank::wild:
            r = UnoRank::blank;
            break;
        case UnoRank::blank:
            r = UnoRank::undefined;
            break;
        case UnoRank::undefined:
            break;
    }

    return r;
}

//default constructor
UnoDeck::UnoDeck(){
    cards.push_back(Card<UnoRank, Color>(UnoRank::zero, Color::red));
    cards.push_back(Card<UnoRank, Color>(UnoRank::zero, Color::blue));
    cards.push_back(Card<UnoRank, Color>(UnoRank::zero, Color::green));
    cards.push_back(Card<UnoRank, Color>(UnoRank::zero, Color::yellow));
    for (UnoRank rank = UnoRank::one; rank <= UnoRank::drawtwo; ++rank) { //loop through rank
        for (Color color = Color::red; color <= Color::yellow; ++color) { //loop through color
            cards.push_back(Card<UnoRank, Color>(rank, color));
            cards.push_back(Card<UnoRank, Color>(rank, color)); //push twice
        }
    }

    for (UnoRank rank = UnoRank::drawfour; rank <= UnoRank::blank; ++rank) {
        cards.push_back(Card<UnoRank, Color>(rank, Color::black));
        cards.push_back(Card<UnoRank, Color>(rank, Color::black));
        cards.push_back(Card<UnoRank, Color>(rank, Color::black));
        cards.push_back(Card<UnoRank, Color>(rank, Color::black));
    }
}

std::string printRank(UnoRank r) {
    if(r==UnoRank::zero){
        return  "0";
    }else if(r==UnoRank::one){
        return  "1";
    }else if(r==UnoRank::two){
        return  "2";
    }else if(r==UnoRank::three){
        return  "3";
    }else if(r==UnoRank::four){
        return  "4";
    }else if(r==UnoRank::five){
        return  "5";
    }else if(r==UnoRank::six){
        return  "6";
    }else if(r==UnoRank::seven){
        return  "7";
    }else if(r==UnoRank::eight){
        return  "8";
    }else if(r==UnoRank::nine){
        return  "9";
    }else if(r==UnoRank::skip){
        return  "Skip";
    }else if(r==UnoRank::reverse){
        return  "Reverse";
    }else if(r==UnoRank::drawtwo){
        return  "Drawtwo";
    }else if(r==UnoRank::drawfour){
        return  "Drawfour";
    }else if(r==UnoRank::wild){
        return  "Wild";
    }else if(r==UnoRank::blank){
        return  "Blank";
    }
    return  "?";

}