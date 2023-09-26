#include "Deck.h"

template<typename rank, typename suit>
void Deck<rank, suit>::shuffle() {
    std::random_device device;
    std::mt19937 g(device);

    std::shuffle(CardSet<R,S>::card.begin(), CardSet<R,S>::card.end(), g);
}

template<typename rank, typename suit>
void Deck<rank, suit>::collect(CardSet<rank, suit> & col) {
    if(col.is_empty()) {
        throw(std::runtime_error);
    } else {
        while(!col.is_empty()){
            col >> *this; // #10
        }
    }
}