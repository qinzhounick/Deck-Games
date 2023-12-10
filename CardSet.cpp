//File Name: CardSet.cpp
//Authors: Qinzhou(Nick) Song, Xinyu(Jack) Li
//Email: qinzhounick@wustl.edu, l.xinyujack@wustl.edu
//Summary: source file for CardSet
//  define print, operator>>, is_empty function, 
//  a copy constructor, begin function, end function, add_card function, clear function, erase function,
//  a collect function, collect_if function, and request function

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
        if(i%size == size - NULL_VALUE) {
            os << endl;
        }
        i++;
    }
    os << endl;
}

//print function
template<typename R, typename S>
void CardSet<R, S>::printBooks(ostream& os) {
    int i = 0; //keep track of iterations
    const int PRINT_BOOK = 4;
    sort(cards.begin(), cards.end()); //sort the cards
    R currentRank;
    for(auto & card: cards) {
        //update currentRank and print the next book
        if(i%PRINT_BOOK == 0){
            currentRank = card._rank;
            os << "[" << currentRank << "]";
        }
        i++;
    }
    os << endl;

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
            c.cards.push_back(Card<R, S>(cards[t-NULL_VALUE]._rank, cards[t-NULL_VALUE]._suit));
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
    return cards.back();
}

//add card to cardset
template<typename R, typename S>
void CardSet<R,S>::add_card(Card<R,S> & card){
    cards.push_back(card);
}


template<typename R, typename S>
void CardSet<R,S>::clear() {
    cards.clear();
}

// erase card from the deck
template<typename R, typename S>
void CardSet<R,S>::erase(iter begin, iter end) {
    cards.erase(begin, end);
}

//define collect function
template<typename R, typename S>
void CardSet<R, S>::collect(CardSet<R, S> & col) {
    if(col.is_empty()) { //check if the Cardset passed in is empty
        throw std::runtime_error("runtime error"); //throw runtime error if empty
    } else {
        auto it = col.end();
        std::move(col.begin(), it, std::back_inserter(cards));  //
        col.clear();
    }
}

// define collect_if function
template<typename R, typename S>
void CardSet<R,S>::collect_if(CardSet<R,S> & deck, std::function<bool(Card<R,S>&)> pred) {
    std::copy_if(deck.begin(), deck.end(), std::back_inserter(cards), pred); // if the card exists, deck collects the card
    auto start = std::remove_if(deck.begin(), deck.end(), pred); // remove the card
    deck.erase(start, deck.end()); // erase the null value
}


// request card from the deck or the players
template<typename R, typename S>
bool CardSet<R,S>::request(CardSet<R, S> & cardset, R & rank) {
    //find a card that has the requested rank
    auto iter = std::find_if(cardset.begin(), cardset.end(), [&rank](const Card<R, S>& card) {
        return card._rank == rank;
    });

    if (iter == cardset.end()) { //if rank not found, return false
        return false;
    }

    cards.push_back(std::move(*iter)); // Move the card to this CardSet
    const int advance = 1;
    auto end = iter + advance;
    cardset.erase(iter, end);  //remove from the old card set
    return true;
}