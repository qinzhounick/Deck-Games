#include "GoFishGame.h"

using namespace std;

template <typename s=Suit, typename r=HoldEmRank, typename d=HoldEmDeck>
GoFishGame<Suit, HoldEmRank, HoldEmDeck>::GoFishGame(int argc, char* argv): Game(argc, argv){
    for(HoldEmRank rank = HoldEmRank::two; rank <= HoldEmRank::ace; ++rank){
        int count = std::count_if(goFishDeck.cards.begin(), goFishDeck.cards.end(), [&rank](const Card<R,S> & card) { return card._rank == rank;});
        if(count < 4){
            throw std::runtime_error("Invalid deck for GoFishGame");
        }
    }  
}
