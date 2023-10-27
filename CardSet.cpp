//File Name: CardSet.cpp
//Authors: Qinzhou(Nick) Song, Xinyu(Jack) Li
//Email: qinzhounick@wustl.edu, l.xinyujack@wustl.edu
//Summary: source file for CardSet
//  define print, operator>>, is_empty function, operator>>, 
//  a copy constructor, a getter member function

#include "CardSet.h"

using namespace std;

//print function
template<typename R, typename S>
void CardSet<R, S>::print(ostream& os, size_t size) {
    //int i to track the number of cards printed
    int i = 0;
    sort(cards.begin(), cards.end());
    for(typename vector< Card<R,S> >::iterator itr = cards.begin(); itr != cards.end(); ++itr) {
        //pass cards to ostream using iterator
        os << *itr << " ";
        //make a newline for every 'size'(passed in as parameter)
        //  number of cards
        if(i%size == size-1) {
            os << endl;
        }
        i++;
    }
}

//is_empty function
template<typename R, typename S>
bool CardSet<R,S>::is_empty() {
    //check if vector is empty
    if(cards.empty()) {
        return true;
    } else {
        return false;
    }
}

//overloaded shift operator
template<typename R, typename S>
CardSet<R,S> & CardSet<R,S>::operator>> (CardSet<R,S> & c) {
    try {
        if(cards.empty()) { //check if cards is empty
            throw std::runtime_error("runtime_error"); //throw error
        } else {
            //if not empty, push back last card to another CardSet
            //  and pop the last card
            size_t t = cards.size();
            c.cards.push_back(Card<R, S>(cards[t-1]._rank, cards[t-1]._suit));
            cards.pop_back();
        }
    } catch(std::runtime_error const&) {
        cout << "cardset is empty: " << endl; //print error message
    }
    return *this;
    
}

//copy constructor
template<typename R, typename S>
CardSet<R,S>::CardSet(const CardSet<R,S> & cardSet_cp){
    cards = cardSet_cp.cards;
}

//getter member function
template<typename R, typename S>
vector<Card<R,S> > * CardSet<R,S>::getCards(CardSet<R,S> & cardSet){
    vector<Card<R,S> > *tmp = &cardSet.cards;
    return tmp;
}