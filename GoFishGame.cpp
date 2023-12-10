//File Name: GoFishGame.cpp
//Authors: Qinzhou(Nick) Song, Xinyu(Jack) Li
//Email: qinzhounick@wustl.edu, l.xinyujack@wustl.edu
//Summary: source file for GoFishGame
//  define constructor and functions including collect_books, turn, deal, player
//  define the specializations for constructor and collect_books for different ranks and decks

#include "GoFishGame.h"

using namespace std;
const int TWO_PLAYERS = 2;
const int DECK_NAME = 2;
const int GOFISH_ARGC = 4;
const int GOFISH_BOOK_LEN = 4;
const int GOFISH_PRINT = 20;
const int FIRST_PLAYER = 0;
const int SECOND_PLAYER = 1;

// default constructor for GoFishGame
template <typename r, typename s, typename d>
GoFishGame<r,s,d>::GoFishGame(int argc, const char * argv[]): Game(argc, argv){
    deckType = argv[DECK_NAME];
    CardSet<r, s> emptyCardSet;  //declare empty player hands
    for(int i = GOFISH_INDEX; i<argc; i++) {  //repeat for the number of players given
        goFishHands.push_back(emptyCardSet);  //initialize the hands and books to avoid null
        goFishBooks.push_back(emptyCardSet);
        goFishScores.push_back(std::make_pair(argv[i], 0)); // initialize the score vector with pairs of player+score
    }
    
    // default with HoldEmRank
    for(HoldEmRank rank = HoldEmRank::two; rank <= HoldEmRank::ace; ++rank){
        int count = std::count_if(goFishDeck.cards.begin(), goFishDeck.cards.end(), [&rank](const Card<HoldEmRank,Suit> & card) { return card._rank == rank;});
        if(count < GOFISH_ARGC){
            throw std::runtime_error("Invalid deck for GoFishGame");
        }
    }  
}

// define collect_books default function
template <typename r, typename s, typename d>
bool GoFishGame<r,s,d>::collect_books(int playerNumber){
    bool flag = false;
    // the default deck and rank is HoldEm, so we go through HoldEmRank to check for 4 of kind
    for(HoldEmRank rank = HoldEmRank::two; rank <= HoldEmRank::ace; ++rank){
        std::function<bool(Card<r,s>&)> predicate = [&rank](const Card<r,s> & card) { return card._rank == rank;}; // compare each rank
        // get the count of cards with the same rank and if there are four cards, put it in book
        int count = std::count_if(goFishHands[playerNumber].begin(), goFishHands[playerNumber].end(), predicate);
        if(count >= GOFISH_BOOK_LEN){
            flag = true;
            goFishBooks[playerNumber].collect_if(goFishHands[playerNumber],predicate);
            //calculate scores and update
            int bookNum = std::distance(goFishBooks[playerNumber].begin(), goFishBooks[playerNumber].end()) / GOFISH_BOOK_LEN;
            goFishScores[playerNumber].second=bookNum;
            return flag;
        }
    }
    return flag;
}

// helper function for checking if the input player is numeric or not
bool isNumeric(const std::string& input) {
    for(auto & c: input) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

// define turn function
template <typename r, typename s, typename d>
bool GoFishGame<r,s,d>::turn(int playerNumber){
    bool incorrect_input = true;
    string input_rank;
    string input_player;
    int input_player_index;

    // if the player's hand the deck are both empty, skip turn but not remove the player from the game
    if(goFishHands[playerNumber].is_empty() && goFishDeck.is_empty()){
        cout << "Player " << names[playerNumber] << "'s hand is empty and the deck is empty. Turn skipped" << endl;
        cout << endl << "End of turn: " << endl;
        cout << "Player " << names[playerNumber] << "'s books are: ";
        goFishBooks[playerNumber].printBooks(std::cout);
        cout << endl;
        return false;
    }
    // if only the player's hand is empty but not the deck, then draw one card from the deck
    if(goFishHands[playerNumber].is_empty()){
        goFishDeck >> goFishHands[playerNumber];
        auto last_card = goFishHands[playerNumber].back();
        std::string str = printRank(last_card._rank);
        cout << "Player " << names[playerNumber] << "'s hand is empty. Draw " << str << " from deck" << endl;
        cout << endl;
    }

    
    // print out the initial information of the current player
    cout << "Player " << names[playerNumber] << "'s turn: " << endl;
    cout << "Player " << names[playerNumber] << "'s hand: ";
    goFishHands[playerNumber].print(std::cout, GOFISH_PRINT);
    cout << "Player " << names[playerNumber] << "'s books: ";
    goFishBooks[playerNumber].printBooks(std::cout);

    while(incorrect_input){
        //---------------------------------------CHECK FOR VALID INPUT----------------------------------------
        cout << "What card rank do you want to ask for?(card rank should be in your hand, letters must be capitalized.)" << endl;
        cin >> input_rank;
        cout << "Which player do you want to ask for it from?(Index number of a player; Cannot be your Number)" << endl;
        cout << "E.g. If you want to request from the first player, input '1'; if third player, input '3'..." << endl;
        cin >> input_player;
        
        // check if the input for player is player's index, not anything else
        if(isNumeric(input_player)){
            input_player_index = stoi(input_player) - NULL_VALUE;
        }else{
            cout << "Please input valid player index" << endl;
            continue;
        }
        
        // get the input rank in string type
        auto predicate = [&input_rank](const Card<r,s> & card) { 
                            std::string str = printRank(card._rank);  // convert "rank" type to string type for comparison
                            return str == input_rank;
                        };

        // check if the input rank is in the current player's hand and the input player's index exists
        if(std::find_if(goFishHands[playerNumber].begin(), 
                        goFishHands[playerNumber].end(), 
                        predicate) != goFishHands[playerNumber].end()
           && input_player_index>=0 && input_player_index<(int)names.size() 
           && input_player_index!=playerNumber 
           && std::find(invalidPlayers.begin(),invalidPlayers.end(),input_player_index)==invalidPlayers.end()){

            incorrect_input = false;
            
        }
        // check if the input player is in the current players pool
        if(input_player_index<0 || input_player_index >=(int)names.size() 
        || input_player_index==playerNumber || std::find(invalidPlayers.begin(),invalidPlayers.end(),input_player_index)!=invalidPlayers.end()){
            cout << "Invalid player index. Please try again." << endl;
        }
        // check if the requested card is in the current player's hand
        if(std::find_if(goFishHands[playerNumber].begin(), 
                        goFishHands[playerNumber].end(), 
                        predicate) == goFishHands[playerNumber].end()){
            cout << "Invalid card rank. Please try again." << endl;
        }
    }

    // get the rank of the request card for easier comparison with enum values
    r request_rank = goFishDeck.getRank(input_rank);
    
    // check if the asked player has the requested card
    // if the asked player has the card, get the card and update the books if 4 of kind
    if(goFishHands[playerNumber].request(goFishHands[input_player_index], request_rank)){
        cout << "Request from player " << names[input_player_index] << " succeeded! ";
        cout << "Got " << request_rank << " from player " << names[input_player_index];
        cout << "\n\n";
        //collect books and update scores
        while(collect_books(playerNumber)){}
        return true;
    } else {
        // Go Fish
        // cannot get the card from the asked player, draw a card from the deck
        cout << "Go Fish!" << endl;
        // if the deck is not empty
        if(!goFishDeck.is_empty()) {
            goFishDeck >> goFishHands[playerNumber];
            auto last_card = goFishHands[playerNumber].back();

            //get the string for the rank of the last card
            std::string str = printRank(last_card._rank);
            if(str == input_rank) {
                // draw a card from the deck and the drawed card matches the one in hand
                cout << "GoFish succeeded! Draw " << str << " from deck!" << endl;
                cout << endl;
                // collect books and update scores
                while(collect_books(playerNumber)){}
                return true;
            } else {
                // draw a card from the deck but he drawed card doesn't match anyone in hand
                // end the turn
                cout << "GoFish failed! Draw " << str << " from deck!" << endl;
                // collect books and update scores
                while(collect_books(playerNumber)){}
                cout << endl << "End of turn: " << endl;
                cout << "Player " << names[playerNumber] << "'s hand is: ";
                goFishHands[playerNumber].print(std::cout, GOFISH_PRINT);
                cout << "Player " << names[playerNumber] << "'s books are: ";
                goFishBooks[playerNumber].printBooks(std::cout);
                cout << endl;

                return false;
            }
        } else { // if the deck is empty
            goFishDeck.collect(goFishHands[playerNumber]); // player out of game, deck collects the player's hand
            invalidPlayers.push_back(playerNumber); // add this player in the vector representing players out of game
            cout << "Player " << names[playerNumber] << " is removed from the game" << endl;
        }
    }
    
    //collect books and update scores
    while(collect_books(playerNumber)){}
    // end of turn, print out the hand and books of the player
    cout << endl << "End of turn: " << endl;
    cout << "Player " << names[playerNumber] << "'s hand is: ";
    goFishHands[playerNumber].print(std::cout, GOFISH_PRINT);
    cout << "Player " << names[playerNumber] << "'s books are: ";
    goFishBooks[playerNumber].printBooks(std::cout);
    cout << endl;

    return false;
}

// define deal function
template <typename r, typename s, typename d>
void GoFishGame<r,s,d>::deal(){
    goFishDeck.shuffle(); // shuffle the deck
    // initial card number in players' hands according to the number of players in the game
    const int numCardOnlyTwoPlyr = 7;
    const int numCardTwoMorePlyr = 5;
    int players = (int)names.size();
    if(players == TWO_PLAYERS){  // when only two players, each gets 7 cards
        for(int i = 0; i < numCardOnlyTwoPlyr; i++){
            goFishDeck >> goFishHands[FIRST_PLAYER];
            goFishDeck >> goFishHands[SECOND_PLAYER];
        }
    }else if(players > TWO_PLAYERS){ // when more than players, each gets 5 cards
        for(int i = 0; i < numCardTwoMorePlyr; i++){
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
    // deal cards to players to play
    deal();

    // check if the current is in the invalid players vector, which has the players that are out of game
    // if out of game, move on to the next player
    int players = (int)names.size();
    for(int i = 0; i < players; i++){
        if( std::count(invalidPlayers.begin(),invalidPlayers.end(),i)) continue;
        while(collect_books(i)){}
    }
    
    // if game is not ended, keep calling turn over and over again
    int round = 1;
    while(GAME_NOT_END){
        for(int i = 0; i < players; i++){
            if(std::count(invalidPlayers.begin(),invalidPlayers.end(),i)) continue;
            while(turn(i)){}
        }

        // print the round number and how many books all players have made so far
        cout << "Round " << round << " finished:" << endl;
        for(int i = 0; i < players; i++){
            int bookNum = std::distance(goFishBooks[i].begin(), goFishBooks[i].end()) / 4;
            cout << "Player " << names[i] << " has " << bookNum << " books made" << endl;
        }
        cout << endl;

        // get the total of all books have made
        int sumBooks = 0;
        for(auto & score: goFishScores){
            sumBooks += score.second;
        }

        // the rules for three decks, each one represents the max books a deck can have
        const int HoldEmMax = 13;
        const int PinochleMax = 12;
        const int UnoMax = 28;
        
        // make bool variables for each deck to check the game-over state
        bool HoldEmCondition = (sumBooks==HoldEmMax && deckType=="HoldEm");
        bool PinochleCondition = (sumBooks==PinochleMax && deckType=="Pinochle");
        bool UnoCondition = (sumBooks==UnoMax && deckType=="Uno");
        bool gameEndCondition = (goFishDeck.is_empty() && (HoldEmCondition || PinochleCondition || UnoCondition));
        // if the maximum number of books has reached, or all players are out of game, or there is only player left, game over
        if(gameEndCondition || names.empty() || (int)names.size()==1){
            GAME_NOT_END = false;
            if((int)names.size()==1){
                for(int i = 0; i < players; i++){
                    if(!std::count(invalidPlayers.begin(),invalidPlayers.end(),i)){
                        goFishDeck.collect(goFishHands[i]); // deck collects all cards in the player's hand if the player is out of game(invalid player)
                        invalidPlayers.push_back(i); // put that player in the invalidPlayer vector and generate the message
                        cout << "Player " << names[i] << " is removed from the game" << endl;
                    }
                }
            }

            //  print the players that has the most books
            //  after game ends, we get the book numbers for each player
            //  then, we collect the cards back into goFishDeck
            std::sort(goFishScores.begin(), goFishScores.end(), cmp);
            
            int prev_bookNum = 0;
            cout << "Winners: ";
            for(auto const& it: goFishScores){
                if(prev_bookNum > it.second) break;
                cout << "Player " << it.first << " ";
                prev_bookNum = it.second;
            }
            cout << endl;
        }
        round++;
    }

    return SUCCESS;
}


//-----------------------------------------------Class Template Specializations-----------------------------------------------------
// specialization for GoFishGame constructor with HoldEmRank, Suit, and HoldEmDeck
template <>
GoFishGame<HoldEmRank, Suit, HoldEmDeck>::GoFishGame(int argc, const char* argv[]): Game(argc, argv){
    deckType = argv[DECK_NAME];
    CardSet<HoldEmRank, Suit> emptyCardSet;  //declare empty player hands
    for(int i = GOFISH_INDEX; i<argc; i++) {  //repeat for the number of players given
        goFishHands.push_back(emptyCardSet);  //initialize the hands and books to avoid null
        goFishBooks.push_back(emptyCardSet);
        goFishScores.push_back(std::make_pair(argv[i], 0)); // initialize the score vector with pairs of player+score
    }
    for(HoldEmRank rank = HoldEmRank::two; rank <= HoldEmRank::ace; ++rank){
        int count = std::count_if(goFishDeck.begin(), goFishDeck.end(), [&rank](const Card<HoldEmRank,Suit> & card) { return card._rank == rank;});
        if(count < GOFISH_ARGC){
            throw std::runtime_error("Invalid deck for GoFishGame");
        }
    }  
}


// specialization for GoFishGame constructor with PinochleRank, Suit, and PinochleDeck
template <>
GoFishGame<PinochleRank, Suit, PinochleDeck>::GoFishGame(int argc, const char* argv[]): Game(argc, argv){
    deckType = argv[DECK_NAME];
    CardSet<PinochleRank, Suit> emptyCardSet;  //declare empty player hands
    for(int i = GOFISH_INDEX; i<argc; i++) {  //repeat for the number of players given
        goFishHands.push_back(emptyCardSet);  //initialize the hands and books to avoid null
        goFishBooks.push_back(emptyCardSet);
        goFishScores.push_back(std::make_pair(argv[i], 0));  // initialize the score vector with pairs of player+score
    }
    for(PinochleRank rank = PinochleRank::nine; rank <= PinochleRank::ace; ++rank){
        int count = std::count_if(goFishDeck.begin(), goFishDeck.end(), [&rank](const Card<PinochleRank,Suit> & card) { return card._rank == rank;});
        if(count < GOFISH_ARGC){
            throw std::runtime_error("Invalid deck for GoFishGame");
        }
    }  
}

// specialization for GoFishGame constructor with UnoRank, Suit, and UnoDeck
template <>
GoFishGame<UnoRank, Color, UnoDeck>::GoFishGame(int argc, const char* argv[]): Game(argc, argv){
    deckType = argv[DECK_NAME];
    CardSet<UnoRank, Color> emptyCardSet;  //declare empty player hands
    for(int i = GOFISH_INDEX; i<argc; i++) {  //repeat for the number of players given
        goFishHands.push_back(emptyCardSet);  //initialize the hands and books to avoid null
        goFishBooks.push_back(emptyCardSet);
        goFishScores.push_back(std::make_pair(argv[i], 0));  // initialize the score vector with pairs of player+score
    }
    for(UnoRank rank = UnoRank::zero; rank <= UnoRank::blank; ++rank){
        int count = std::count_if(goFishDeck.begin(), goFishDeck.end(), [&rank](const Card<UnoRank,Color> & card) { return card._rank == rank;});
        if(count < GOFISH_ARGC){
            throw std::runtime_error("Invalid deck for GoFishGame");
        }
    }  
}


//-----------------------------------------------collect_books Specializations-----------------------------------------------------
// specialization for collect_books with HoldEmRank, Suit, and HoldEmDeck
template <>
bool GoFishGame<HoldEmRank, Suit, HoldEmDeck>::collect_books(int playerNumber){
    bool flag = false;
    // we go through HoldEmRank to check for 4 of kind
    for(HoldEmRank rank = HoldEmRank::two; rank <= HoldEmRank::ace; ++rank){
        auto predicate = [&rank](const Card<HoldEmRank,Suit> & card) { return card._rank == rank;};
        // get the count of cards with the same rank and if there are four cards, put it in book
        int count = std::count_if(goFishHands[playerNumber].begin(), goFishHands[playerNumber].end(), predicate);
        if(count >= GOFISH_BOOK_LEN){
            flag = true;
            goFishBooks[playerNumber].collect_if(goFishHands[playerNumber],predicate);
            //calculate scores and update
            int bookNum = std::distance(goFishBooks[playerNumber].begin(), goFishBooks[playerNumber].end()) / GOFISH_BOOK_LEN;
            goFishScores[playerNumber].second=bookNum;
            return flag;
        }
    }  

    return flag;
}

// specialization for collect_books with PinochleRank, Suit, and PinochleDeck
template <>
bool GoFishGame<PinochleRank, Suit, PinochleDeck>::collect_books(int playerNumber){
    bool flag = false;
    // we go through PinochleRank to check for 4 of kind
    for(PinochleRank rank = PinochleRank::nine; rank <= PinochleRank::ace; ++rank){
        auto predicate = [&rank](const Card<PinochleRank,Suit> & card) { return card._rank == rank;};
        // get the count of cards with the same rank and if there are four cards, put it in book
        int count = std::count_if(goFishHands[playerNumber].begin(), goFishHands[playerNumber].end(), predicate);
        // since there are two poker decks in Pincochle deck, we need to make sure if greater than 4, then collect books
        if(count >= GOFISH_BOOK_LEN){
            flag = true;
            goFishBooks[playerNumber].collect_if(goFishHands[playerNumber],predicate);
            //calculate scores and update
            int bookNum = std::distance(goFishBooks[playerNumber].begin(), goFishBooks[playerNumber].end()) / GOFISH_BOOK_LEN;
            goFishScores[playerNumber].second=bookNum;
            return flag;
        }
    }
    return flag;
}

// specialization for collect_books with UnoRank, Suit, and UnoDeck
template <>
bool GoFishGame<UnoRank, Color, UnoDeck>::collect_books(int playerNumber){
    bool flag = false;
    // we go through UnoRank to check for 4 of kind
    for(UnoRank rank = UnoRank::zero; rank <= UnoRank::blank; ++rank){
        auto predicate = [&rank](const Card<UnoRank,Color> & card) { return card._rank == rank;};
        // get the count of cards with the same rank and if there are four cards, put it in book
        int count = std::count_if(goFishHands[playerNumber].begin(), goFishHands[playerNumber].end(), predicate);
        if(count >= GOFISH_BOOK_LEN){
            flag = true;
            goFishBooks[playerNumber].collect_if(goFishHands[playerNumber],predicate);
            //calculate scores and update
            int bookNum = std::distance(goFishBooks[playerNumber].begin(), goFishBooks[playerNumber].end()) / GOFISH_BOOK_LEN;
            goFishScores[playerNumber].second=bookNum;
            return flag;
        }
    }
    return flag; 
}