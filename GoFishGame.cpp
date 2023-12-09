#include "GoFishGame.h"

using namespace std;
const int LAST_TWO_PLAYERS = 2;
const int DECK_NAME = 2;
const int GOFISH_ARGC = 4;
const int GOFISH_BOOK_LEN = 4;
const int GOFISH_PRINT = 20;

template <typename r, typename s, typename d>
GoFishGame<r,s,d>::GoFishGame(int argc, const char * argv[]): Game(argc, argv){
    deckType = argv[DECK_NAME];
    CardSet<r, s> emptyCardSet;  //declare empty player hands
    for(int i = INDEX; i<argc; i++) {  //repeat for the number of players given
        goFishHands.push_back(emptyCardSet);  //initialize the hands and books to avoid null
        goFishBooks.push_back(emptyCardSet); 
    }

    for(HoldEmRank rank = HoldEmRank::two; rank <= HoldEmRank::ace; ++rank){
        int count = std::count_if(goFishDeck.cards.begin(), goFishDeck.cards.end(), [&rank](const Card<HoldEmRank,Suit> & card) { return card._rank == rank;});
        if(count < GOFISH_ARGC){
            throw std::runtime_error("Invalid deck for GoFishGame");
        }
    }  
}

template <typename r, typename s, typename d>
bool GoFishGame<r,s,d>::collect_books(int playerNumber){
    bool flag = false;
    for(HoldEmRank rank = HoldEmRank::two; rank <= HoldEmRank::ace; ++rank){
        std::function<bool(Card<r,s>&)> predicate = [&rank](const Card<r,s> & card) { return card._rank == rank;};
        int count = std::count_if(goFishHands[playerNumber].begin(), goFishHands[playerNumber].end(), predicate);
        if(count >= GOFISH_ARGC){
            flag = true;
            goFishBooks[playerNumber].collect_if(goFishHands[playerNumber],predicate);
            return flag;
        }
    }

    return flag;
}


template <typename r, typename s, typename d>
bool GoFishGame<r,s,d>::turn(int playerNumber){
    bool incorrect_input = true;
    string input_rank;
    string input_player;
    int input_player_index;
    cout << "Player " << names[playerNumber] << "'s hand is: ";
    goFishHands[playerNumber].print(std::cout, GOFISH_PRINT);
    cout << "Player " << names[playerNumber] << "'s books are: ";
    goFishBooks[playerNumber].print(std::cout, GOFISH_PRINT);

    while(incorrect_input){
        //---------------------------------------CHECK FOR VALID INPUT----------------------------------------
        cout << "What card rank do you want to ask for?(card rank should be in your hand)" << endl;
        cin >> input_rank;
        cout << "Which player do you want to ask for it from?(Index number of a player; Cannot be your Number)" << endl;
        cin >> input_player;

        input_player_index = stoi(input_player);
        auto predicate = [&input_rank](const Card<r,s> & card) { 
                            std::string str = printRank(card._rank); 
                            return str == input_rank;
                        };

        if(std::find_if(goFishHands[playerNumber].begin(), 
                        goFishHands[playerNumber].end(), 
                        predicate) != goFishHands[playerNumber].end()
           && input_player_index>=0 && input_player_index<=(int)names.size()-1 
           && input_player_index!=playerNumber){

            incorrect_input = false;
            cout << "Invalid input. Please try again." << endl;
            
        }
    }

    
    r request_rank = goFishDeck.getRank(input_rank);
    

    if(goFishHands[playerNumber].request(goFishHands[input_player_index], request_rank)){
        while(collect_books(playerNumber)){
        }
        return true;
    } else {
        cout << "Go Fish!" << endl;
        if(!goFishDeck.is_empty()) {
            goFishDeck >> goFishHands[playerNumber];
            auto last_card = goFishHands[playerNumber].back();

            //get the string for the rank of the last card
            std::string str = printRank(last_card._rank);
            if(str == input_rank) {
                return true;
            } else {
                return false;
            }
        } else {//--------------------------------ASK TA OR PROFESSOR----------------------------------------------------------
            goFishDeck.collect(goFishHands[playerNumber]);
            int bookNum = std::distance(goFishBooks[playerNumber].begin(), goFishBooks[playerNumber].end()) / GOFISH_BOOK_LEN;
            goFishScores.push_back({names[playerNumber], bookNum});
            invalidPlayers.push_back(playerNumber);
            cout << "Player " << names[playerNumber] << " is removed from the game" << endl;
        }


    }

    cout << endl << "End of turn: " << endl;
    cout << "Player " << names[playerNumber] << "'s hand is: ";
    goFishHands[playerNumber].print(std::cout, GOFISH_PRINT);
    cout << "Player " << names[playerNumber] << "'s books are: ";
    goFishBooks[playerNumber].print(std::cout, GOFISH_PRINT);

    return false;
}


template <typename r, typename s, typename d>
void GoFishGame<r,s,d>::deal(){
    goFishDeck.shuffle();
    const int numCardTwoMorePlyr = 7;
    const int numCardOnlyTwoPlyr = 5;
    int players = (int)names.size() - NULL_VALUE;
    if(players == LAST_TWO_PLAYERS){
        for(int j = 0; j < numCardTwoMorePlyr; j++){
            goFishDeck >> goFishHands[0];
            goFishDeck >> goFishHands[1];
        }
    }else if(players > LAST_TWO_PLAYERS){
        for(int i = 0; i < numCardOnlyTwoPlyr; i++){
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
template <typename r, typename s, typename d>
int GoFishGame<r,s,d>::play(){
    bool GAME_NOT_END = true;
    deal();


    int players = (int)names.size();
    for(int i = 0; i < players; i++){
        if( std::count(invalidPlayers.begin(),invalidPlayers.end(),i)) continue;
        while(collect_books(i)){}
    }
    
    int round = 1;
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

        int sumBooks = 0; //std::accumulate(goFishScores.begin(), goFishScores.end(), 0);

        const int HoldEmMax = 13;
        const int PinochleMax = 26;
        const int UnoMax = 28;
        bool HoldEmCondition = (sumBooks==HoldEmMax && deckType=="HoldEm");
        bool PinochleCondition = (sumBooks==PinochleMax && deckType=="Pinochle");
        bool UnoCondition = (sumBooks==UnoMax && deckType=="Uno");
        bool gameEndCondition = (goFishDeck.is_empty() && (HoldEmCondition || PinochleCondition || UnoCondition));
        
        if(gameEndCondition || names.empty() || (int)names.size()==1){
            GAME_NOT_END = false;
            if((int)names.size()==1){
                for(int i = 0; i < players; i++){
                    if(!std::count(invalidPlayers.begin(),invalidPlayers.end(),i)){
                        goFishDeck.collect(goFishHands[i]);
                        int bookNum = std::distance(goFishBooks[i].begin(), goFishBooks[i].end()) / 4;
                        goFishScores.push_back({names[i], bookNum});
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
            for(auto const& it: goFishScores){
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
GoFishGame<HoldEmRank, Suit, HoldEmDeck>::GoFishGame(int argc, const char* argv[]): Game(argc, argv){
    CardSet<HoldEmRank, Suit> emptyCardSet;  //declare empty player hands
    for(int i = INDEX; i<argc; i++) {  //repeat for the number of players given
        goFishHands.push_back(emptyCardSet);  //initialize the hands and books to avoid null
        goFishBooks.push_back(emptyCardSet); 
    }
    for(HoldEmRank rank = HoldEmRank::two; rank <= HoldEmRank::ace; ++rank){
        int count = std::count_if(goFishDeck.begin(), goFishDeck.end(), [&rank](const Card<HoldEmRank,Suit> & card) { return card._rank == rank;});
        if(count < GOFISH_ARGC){
            throw std::runtime_error("Invalid deck for GoFishGame");
        }
    }  
}



template <>
GoFishGame<PinochleRank, Suit, PinochleDeck>::GoFishGame(int argc, const char* argv[]): Game(argc, argv){
    CardSet<PinochleRank, Suit> emptyCardSet;  //declare empty player hands
    for(int i = INDEX; i<argc; i++) {  //repeat for the number of players given
        goFishHands.push_back(emptyCardSet);  //initialize the hands and books to avoid null
        goFishBooks.push_back(emptyCardSet); 
    }
    for(PinochleRank rank = PinochleRank::nine; rank <= PinochleRank::ace; ++rank){
        int count = std::count_if(goFishDeck.begin(), goFishDeck.end(), [&rank](const Card<PinochleRank,Suit> & card) { return card._rank == rank;});
        if(count < GOFISH_ARGC){
            throw std::runtime_error("Invalid deck for GoFishGame");
        }
    }  
}

template <>
GoFishGame<UnoRank, Color, UnoDeck>::GoFishGame(int argc, const char* argv[]): Game(argc, argv){
    CardSet<UnoRank, Color> emptyCardSet;  //declare empty player hands
    for(int i = INDEX; i<argc; i++) {  //repeat for the number of players given
        goFishHands.push_back(emptyCardSet);  //initialize the hands and books to avoid null
        goFishBooks.push_back(emptyCardSet); 
    }
    for(UnoRank rank = UnoRank::zero; rank <= UnoRank::blank; ++rank){
        int count = std::count_if(goFishDeck.begin(), goFishDeck.end(), [&rank](const Card<UnoRank,Color> & card) { return card._rank == rank;});
        if(count < GOFISH_ARGC){
            throw std::runtime_error("Invalid deck for GoFishGame");
        }
    }  
}


//-----------------------------------------------collect_books Specializations-----------------------------------------------------
template <>
bool GoFishGame<HoldEmRank, Suit, HoldEmDeck>::collect_books(int playerNumber){
    bool flag = false;
    for(HoldEmRank rank = HoldEmRank::two; rank <= HoldEmRank::ace; ++rank){
        auto predicate = [&rank](const Card<HoldEmRank,Suit> & card) { return card._rank == rank;};
        int count = std::count_if(goFishHands[playerNumber].begin(), goFishHands[playerNumber].end(), predicate);
        if(count >= GOFISH_ARGC){
            flag = true;
            goFishBooks[playerNumber].collect_if(goFishHands[playerNumber],predicate);
            return flag;
        }
    }  

    return flag;
}

template <>
bool GoFishGame<PinochleRank, Suit, PinochleDeck>::collect_books(int playerNumber){
    bool flag = false;
    for(PinochleRank rank = PinochleRank::nine; rank <= PinochleRank::ace; ++rank){
        auto predicate = [&rank](const Card<PinochleRank,Suit> & card) { return card._rank == rank;};
        int count = std::count_if(goFishHands[playerNumber].begin(), goFishHands[playerNumber].end(), predicate);
        if(count >= GOFISH_ARGC){
            flag = true;
            goFishBooks[playerNumber].collect_if(goFishHands[playerNumber],predicate);
            return flag;
        }
    }
    return flag;
}

template <>
bool GoFishGame<UnoRank, Color, UnoDeck>::collect_books(int playerNumber){
    bool flag = false;
    for(UnoRank rank = UnoRank::zero; rank <= UnoRank::blank; ++rank){
        auto predicate = [&rank](const Card<UnoRank,Color> & card) { return card._rank == rank;};
        int count = std::count_if(goFishHands[playerNumber].begin(), goFishHands[playerNumber].end(), predicate);
        if(count >= GOFISH_ARGC){
            flag = true;
            goFishBooks[playerNumber].collect_if(goFishHands[playerNumber],predicate);
            return flag;
        }
    }
    return flag; 
}