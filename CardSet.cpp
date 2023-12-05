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

//constructor that takes a vector of cards
template<typename R, typename S>
CardSet<R,S>::CardSet(std::vector<Card<R, S> > &&vec) : cards(std::move(vec)){}
//copy constructor 
template<typename R, typename S>
CardSet<R,S>::CardSet(const CardSet<R,S> & cardSet_cp){
    cards = cardSet_cp.cards;
}

// //copy constructor 2
// template<typename R, typename S>
// CardSet<R,S>::CardSet(const vector<Card<R,S> > & card_cp){
//     cards = card_cp;
// }

/*
//getter member function
template<typename R, typename S>
vector<Card<R,S> > * CardSet<R,S>::getCards(CardSet<R,S> & cardSet){
    vector<Card<R,S> > *tmp = &cardSet.cards;
    return tmp;
}
*/

//begin function returns an iterator that points to cards.begin()
template<typename R, typename S>
typename vector<Card<R,S> >::iterator CardSet<R,S>::begin() {
    return cards.begin();
}

//end function returns an iterator that points to cards.end()
template<typename R, typename S>
typename vector<Card<R,S> >::iterator CardSet<R,S>::end() {
    return cards.end();
}

//back function returns the last card in the cardset
template<typename R, typename S>
Card<R,S> CardSet<R,S>::back() {
    if (!cards.empty()) return cards.back();
}

template<typename R, typename S>
void CardSet<R,S>::add_card(Card<R,S> & card){
    cards.push_back(card);
}

template<typename R, typename S>
void CardSet<R,S>::clear() {
    cards.clear();
}

template<typename R, typename S>
void CardSet<R,S>::erase(iter begin, iter end) {
    cards.erase(begin, end);
}

//define collect function
template<typename R, typename S>
void CardSet<R, S>::collect(CardSet<R, S> & col) {
    if(col.is_empty()) { //check if the Card passed in is empty
        throw std::runtime_error("runtime error"); //throw runtime error if empty
    } else {
        auto it = col.end();
        std::move(col.begin(), it, std::back_inserter(cards));  // ##
        col.clear();
    }
}

template<typename R, typename S>
void collect_if(CardSet<R,S> deck, std::function<bool(Card<R,S>&)> pred) {
    std::copy_if(deck.begin(), deck.end(), std::back_inserter(CardSet<R,S>::begin()), pred);
    deck.erase(std::remove_if(deck.begin(), deck.end(), pred), deck.end());
}

template<typename R, typename S>
bool CardSet<R,S>::request(CardSet<R, S> & cardset, R & rank) {
    auto iter = std::find(cardset.begin(), cardset.end(), [&rank](const Card<R,S> & card) { return card._rank == rank;});

    if (iter == cardset.end()) {
        return false;
    }

    cards.push_back(std::move(*iter)); // Move the card to this CardSet
    cardset.erase(iter);
    return true;
}