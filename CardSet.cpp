#include "CardSet.h"

template<typename R, typename S>
void CardSet<R, S>::print(ostream& os, size_t size) {
    int i = 0;
    for(typename vector< Card<R,S> >::iterator itr = cards.begin(); itr != cards.end(); ++itr) {
        os << *itr << " ";
        if(i%size == size-1) {
            os << endl;
        }
        i++;
    }
}

template<typename R, typename S>
bool CardSet<R,S>::is_empty() {
    if(cards.empty()) {
        return true;
    } else {
        return false;
    }
}

template<typename R, typename S>
CardSet<R,S> & CardSet<R,S>::operator>> (CardSet<R,S> & c) {
    try {
        if(cards.empty()) {
            throw std::runtime_error("runtime_error");
        } else {
            size_t t = cards.size();
            c.cards.push_back(Card<R, S>(cards[t-1]._rank, cards[t-1]._suit));
            cards.pop_back();
        }
    } catch(std::runtime_error const&) {
        cout << "cardset is empty: " << endl;
    }
    return *this;
    
}

