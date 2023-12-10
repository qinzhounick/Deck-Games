//File Name: CardSet.h
//Authors: Qinzhou(Nick) Song, Xinyu(Jack) Li
//Email: qinzhounick@wustl.edu, l.xinyujack@wustl.edu
//Summary: header file for CardSet
//  declare base class CardSet
#pragma once
#include "Card_T.h"

using namespace std;
const int NULL_VALUE = 1;

//base template class CardSet
template <typename R, typename S>
class CardSet {
    protected:
        //vector cards to hold Card type objects
        std::vector<Card<R, S> > cards;
    public:
        //overloaded shift operator
        CardSet<R,S> & operator>> (CardSet<R,S> & c);
        //print function to print cards in vector cards
        void print(ostream& os, size_t size);
        //print books for GoFishGame
        void printBooks(ostream& os);
        //is_empty function to check if vector cards is empty
        bool is_empty();
        //Defualt constructor
        CardSet() = default;
        //Constructor that takes a vector of cards
        CardSet(std::vector<Card<R, S> > &&vec);
        //copy constructor
        CardSet(const CardSet<R,S> & cardSet_cp);
        // add cards function
        void add_card(Card<R,S> & card);
        // two different non-static accessor methods
        //static std::vector<Card<R,S> > * getCards(CardSet<R,S> & cardSet); 
        typename std::vector<Card<R,S> >::iterator begin(); //begin function
        typename std::vector<Card<R,S> >::iterator end(); //end function
        Card<R,S> back(); //back function

        //define types
        typedef Card<R, S> card_type;
        typedef typename vector<Card<R, S>>::iterator iter;
        typedef R rank_type;
        typedef S suit_type;

        void clear(); // clear the cards
        void erase(iter begin, iter end); // erase card
        void collect(CardSet<R, S> & col); //collect cards from CardSet back to deck
        
        void collect_if(CardSet<R, S> & deck, std::function<bool (Card<R, S>&)> pred); //only collect cards that meet a certain criteria
        bool request(CardSet<R, S> & cardset, R & rank); // request card from the player or deck
        
};

//inclusion guard
#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE
#include "CardSet.cpp"
#endif