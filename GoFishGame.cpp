#include "GoFishGame.h"

using namespace std;

template <typename s, typename r, typename d>
GoFishGame<s,r,d>::GoFishGame(int argc, char * argv): Game(argc, argv){
    CardSet<r, s> emptyCardSet;  //declare empty player hands
    for(int i = INDEX; i<argc; i++) {  //repeat for the number of players given
        goFishHands.push_back(emptyCardSet);  //initialize the hands and books to avoid null
        goFishBooks.push_back(emptyCardSet); 
    }

    for(HoldEmRank rank = HoldEmRank::two; rank <= HoldEmRank::ace; ++rank){
        int count = std::count_if(goFishDeck.cards.begin(), goFishDeck.cards.end(), [&rank](const Card<HoldEmRank,Suit> & card) { return card._rank == rank;});
        if(count < 4){
            throw std::runtime_error("Invalid deck for GoFishGame");
        }
    }  
}

template <typename s, typename r, typename d>
bool GoFishGame<s,r,d>::collect_books(int playerNumber){
    bool flag = false;
    for(HoldEmRank rank = HoldEmRank::two; rank <= HoldEmRank::ace; ++rank){
        std::function<bool(Card<r,s>&)> predicate = [&rank](const Card<r,s> & card) { return card._rank == rank;};
        int count = std::count_if(goFishHands[playerNumber].begin(), goFishHands[playerNumber].end(), predicate);
        if(count >= 4){
            flag = true;
            goFishBooks[playerNumber].collect_if(goFishHands[playerNumber],predicate);
            return flag;
        }
    }

    return flag;
}


const int GOFISH_PRINT = 7;
template <typename s, typename r, typename d>
bool GoFishGame<s,r,d>::turn(int playerNumber){
    bool incorrect_input = true;
    string input_rank;
    int input_player;
    cout << "Player " << names[playerNumber] << "'s hand is: ";
    goFishHands[playerNumber].print(std::cout, GOFISH_PRINT);
    cout << "Player " << names[playerNumber] << "'s books are: ";
    goFishBooks[playerNumber].print(std::cout, GOFISH_PRINT);

    while(incorrect_input){
        cout << "What card rank do you want to ask for?(card rank should be in your hand)" << endl;
        cin >> input_rank;
        cout << "Which player do you want to ask for it from?(Number of a player; Cannot be your Number)" << endl;
        cin >> input_player;

        if(std::find_if(goFishHands[playerNumber].begin(), 
                        goFishHands[playerNumber].end(), 
                        [&input_rank](const Card<r,s> & card) { return card._rank == input_rank;}) 
           && input_player>=0 && input_player<=(int)names.size()-1 && input_player!=playerNumber){

            incorrect_input = false;
            
        }
    }

    if(request(goFishHands[input_player], input_rank)){
        while(collect_books(playerNumber)){
        }
        return true;
    } else {
        cout << "Go Fish!" << endl;
        if(!goFishDeck.is_empty()) {
            goFishDeck >> goFishHands[playerNumber];
            auto it_card = std::prev(numbers.end());
            if(it_card._rank == input_rank) {
                return true;
            } else {
                return false;
            }
        } else {//--------------------------------ASK TA OR PROFESSOR----------------------------------------------------------
            goFishDeck.collect(goFishHands[playerNumber]);
            goFishDeck.collect(goFishBooks[playerNumber]);
            int bookNum = std::distance(goFishBooks[playerNumber].begin(), goFishBooks[playerNumber].end()) / 4;
            goFishScores.insert({names[playerNumber], bookNum});
            invalidPlayers.push_back(playerNumber);
            cout << "Player " << names[playerNumber] << " is removed from the game" << endl;
        }


    }

    return false;
}


template <typename s, typename r, typename d>
void GoFishGame<s,r,d>::deal(){
    goFishDeck.shuffle();
    int players = (int)names.size() - 1;
    if(players == 2){
        for(int j = 0; j < 7; j++){
            goFishDeck >> goFishHands[0];
            goFishDeck >> goFishHands[1];
        }
    }else if(players > 2){
        for(int i = 0; i < 5; i++){
            for(int j = 0; j < players; j++){
               goFishDeck >> goFishHands[j]; 
            }
        }
    }

}

//helper function to help sorting player books
bool cmp(pair<std::string, int>& a, pair<std::string, int>& b)
{
    return a.second > b.second;
}

//play function
template <typename s, typename r, typename d>
int GoFishGame<s,r,d>::play(){
    bool GAME_NOT_END = true;
    deal();


    int players = (int)names.size();
    for(int i = 0; i < players; i++){
        if( std::count(invalidPlayers.begin(),invalidPlayers.end(),i)) continue;
        while(collect_books(i)){}
    }
    
    int round = 1;
    int bookNum = 0;
    while(GAME_NOT_END){
        for(int i = 0; i < players; i++){
            if(std::count(invalidPlayers.begin(),invalidPlayers.end(),i)) continue;
            while(turn(i)){}
        }

        cout << "Round " << round << " finished:" << endl;
        for(int i = 0; i < players; i++){
            int bookNum = std::distance(goFishBooks[i].begin(), goFishBooks[i].end()) / 4;
            cout << "Player " << names[i] << " has " << bookNum << " books made" << endl;
        }

        if(goFishDeck.is_empty() || names.empty() || (int)names.size()==1){
            GAME_NOT_END = false;
            if((int)names.size()==1){
                for(int i = 0; i < players; i++){
                    if(!std::count(invalidPlayers.begin(),invalidPlayers.end(),i)){
                        goFishDeck.collect_books(goFishBooks[i]);
                        goFishDeck.collect_books(goFishHands[i]);
                        int bookNum = std::distance(goFishBooks[i].begin(), goFishBooks[i].end()) / 4;
                        goFishScores.insert({names[i], bookNum});
                        invalidPlayers.push_back(i);
                        cout << "Player " << names[i] << " is removed from the game" << endl;
                    }
                }
            }
            //print the players that has the most books
            //  after game ends, we get the book numbers for each player
            //  then, we collect the cards back into goFishDeck

            std::sort(goFishScores.begin(), goFishScores.end(), cmp);
            
            int prev_bookNum = 0;
            for(auto it = goFishScores.begin(); it != goFishScores.end(); ++it){
                if(prev_bookNum > it.second) break;
                cout << "Player " << it.first << " ";
                prev_bookNum = it.second;
            }
        }
        round++;
    }

    return SUCCESS;
}


//-----------------------------------------------Class Template Specializations-----------------------------------------------------
template <>
GoFishGame<Suit, HoldEmRank, HoldEmDeck>::GoFishGame(int argc, char* argv): Game(argc, argv){
    CardSet<HoldEmRank, Suit> emptyCardSet;  //declare empty player hands
    for(int i = INDEX; i<argc; i++) {  //repeat for the number of players given
        goFishHands.push_back(emptyCardSet);  //initialize the hands and books to avoid null
        goFishBooks.push_back(emptyCardSet); 
    }
    for(HoldEmRank rank = HoldEmRank::two; rank <= HoldEmRank::ace; ++rank){
        int count = std::count_if(goFishDeck.cards.begin(), goFishDeck.cards.end(), [&rank](const Card<HoldEmRank,Suit> & card) { return card._rank == rank;});
        if(count < 4){
            throw std::runtime_error("Invalid deck for GoFishGame");
        }
    }  
}

// template <>
// GoFishGame<Suit, PinochleRank, HoldEmDeck>::GoFishGame(int argc, char* argv): Game(argc, argv){
//     CardSet<PinochleRank, Suit> emptyCardSet;  //declare empty player hands
//     for(int i = INDEX; i<argc; i++) {  //repeat for the number of players given
//         goFishHands.push_back(emptyCardSet);  //initialize the hands and books to avoid null
//         goFishBooks.push_back(emptyCardSet); 
//     }
//     for(PinochleRank rank = PinochleRank::nine; rank <= PinochleRank::ace; ++rank){
//         int count = std::count_if(goFishDeck.cards.begin(), goFishDeck.cards.end(), [&rank](const Card<PinochleRank,Suit> & card) { return card._rank == rank;});
//         if(count < 4){
//             throw std::runtime_error("Invalid deck for GoFishGame");
//         }
//     }  
// }

// template <>
// GoFishGame<Suit,HoldEmRank, PinochleDeck>::GoFishGame(int argc, char* argv): Game(argc, argv){
//     CardSet<HoldEmRank, Suit> emptyCardSet;  //declare empty player hands
//     for(int i = INDEX; i<argc; i++) {  //repeat for the number of players given
//         goFishHands.push_back(emptyCardSet);  //initialize the hands and books to avoid null
//         goFishBooks.push_back(emptyCardSet); 
//     }
//     for(HoldEmRank rank = HoldEmRank::two; rank <= HoldEmRank::ace; ++rank){
//         int count = std::count_if(goFishDeck.cards.begin(), goFishDeck.cards.end(), [&rank](const Card<HoldEmRank,Suit> & card) { return card._rank == rank;});
//         if(count < 4){
//             throw std::runtime_error("Invalid deck for GoFishGame");
//         }
//     }  
// }

template <>
GoFishGame<Suit, PinochleRank, PinochleDeck>::GoFishGame(int argc, char* argv): Game(argc, argv){
    CardSet<PinochleRank, Suit> emptyCardSet;  //declare empty player hands
    for(int i = INDEX; i<argc; i++) {  //repeat for the number of players given
        goFishHands.push_back(emptyCardSet);  //initialize the hands and books to avoid null
        goFishBooks.push_back(emptyCardSet); 
    }
    for(PinochleRank rank = PinochleRank::nine; rank <= PinochleRank::ace; ++rank){
        int count = std::count_if(goFishDeck.cards.begin(), goFishDeck.cards.end(), [&rank](const Card<PinochleRank,Suit> & card) { return card._rank == rank;});
        if(count < 4){
            throw std::runtime_error("Invalid deck for GoFishGame");
        }
    }  
}

template <>
GoFishGame<Color, UnoRank, UnoDeck>::GoFishGame(int argc, char* argv): Game(argc, argv){
    CardSet<UnoRank, Color> emptyCardSet;  //declare empty player hands
    for(int i = INDEX; i<argc; i++) {  //repeat for the number of players given
        goFishHands.push_back(emptyCardSet);  //initialize the hands and books to avoid null
        goFishBooks.push_back(emptyCardSet); 
    }
    for(UnoRank rank = UnoRank::zero; rank <= UnoRank::blank; ++rank){
        int count = std::count_if(goFishDeck.cards.begin(), goFishDeck.cards.end(), [&rank](const Card<UnoRank,Color> & card) { return card._rank == rank;});
        if(count < 4){
            throw std::runtime_error("Invalid deck for GoFishGame");
        }
    }  
}


//-----------------------------------------------collect_books Specializations-----------------------------------------------------
template <>
bool GoFishGame<Suit, HoldEmRank, HoldEmDeck>::collect_books(int playerNumber){
    bool flag = false;
    for(HoldEmRank rank = HoldEmRank::two; rank <= HoldEmRank::ace; ++rank){
        std::function<bool(Card<HoldEmRank,Suit>&)> predicate = [&rank](const Card<HoldEmRank,Suit> & card) { return card._rank == rank;};
        int count = std::count_if(goFishHands[playerNumber].begin(), goFishHands[playerNumber].end(), predicate);
        if(count >= 4){
            flag = true;
            goFishBooks[playerNumber].collect_if(goFishHands[playerNumber],predicate);
            return flag;
        }
    }  

    return flag;
}

template <>
bool GoFishGame<Suit, PinochleRank, HoldEmDeck>::collect_books(int playerNumber){
    bool flag = false;
    for(PinochleRank rank = PinochleRank::nine; rank <= PinochleRank::ace; ++rank){
        std::function<bool(Card<PinochleRank, Suit>&)> predicate = [&rank](const Card<PinochleRank,Suit> & card) { return card._rank == rank;};
        int count = std::count_if(goFishHands[playerNumber].begin(), goFishHands[playerNumber].end(), predicate);
        if(count >= 4){
            flag = true;
            goFishBooks[playerNumber].collect_if(goFishHands[playerNumber],predicate);
            return flag;
        }
    }  
    return flag;
}

template <>
bool GoFishGame<Suit, HoldEmRank, PinochleDeck>::collect_books(int playerNumber){
    bool flag = false;
    for(HoldEmRank rank = HoldEmRank::two; rank <= HoldEmRank::ace; ++rank){
        std::function<bool(Card<HoldEmRank, Suit>&)> predicate = [&rank](const Card<HoldEmRank,Suit> & card) { return card._rank == rank;};
        int count = std::count_if(goFishHands[playerNumber].begin(), goFishHands[playerNumber].end(), predicate);
        if(count >= 4){
            flag = true;
            goFishBooks[playerNumber].collect_if(goFishHands[playerNumber],predicate);
            return flag;
        }
    }  
    return flag;
}

template <>
bool GoFishGame<Suit, PinochleRank, PinochleDeck>::collect_books(int playerNumber){
    bool flag = false;
    for(PinochleRank rank = PinochleRank::nine; rank <= PinochleRank::ace; ++rank){
        std::function<bool(Card<PinochleRank, Suit>&)> predicate = [&rank](const Card<PinochleRank,Suit> & card) { return card._rank == rank;};
        int count = std::count_if(goFishHands[playerNumber].begin(), goFishHands[playerNumber].end(), predicate);
        if(count >= 4){
            flag = true;
            goFishBooks[playerNumber].collect_if(goFishHands[playerNumber],predicate);
            return flag;
        }
    }
    return flag;
}

template <>
bool GoFishGame<Color, UnoRank, UnoDeck>::collect_books(int playerNumber){
    bool flag = false;
    for(UnoRank rank = UnoRank::zero; rank <= UnoRank::blank; ++rank){
        std::function<bool(Card<UnoRank,Color>&)> predicate = [&rank](const Card<UnoRank,Color> & card) { return card._rank == rank;};
        int count = std::count_if(goFishHands[playerNumber].begin(), goFishHands[playerNumber].end(), predicate);
        if(count >= 4){
            flag = true;
            goFishBooks[playerNumber].collect_if(goFishHands[playerNumber],predicate);
            return flag;
        }
    }
    return flag; 
}