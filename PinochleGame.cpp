//File Name: PinochleGame.cpp
//Authors: Qinzhou(Nick) Song, Xinyu(Jack) Li
//Email: qinzhounick@wustl.edu, l.xinyujack@wustl.edu
//Summary: source file for PinochleGame
//  define constructor and functions 

#include "PinochleGame.h"

using namespace std;

//PinochleGame constructor
//  construct base class and initialize state
PinochleGame::PinochleGame(int argc, const char * argv[]): Game(argc, argv) {
    CardSet<PinochleRank, Suit> playerHand;  //declare empty player hands
    for(int i = INDEX; i<argc; i++) {  //repeat for the number of players given
        pinochleHands.push_back(playerHand);  //push hand to pinochleHands
    }
}

//deal function
void PinochleGame::deal() {
    while(!pinochleDeck.is_empty()) {  //deal all the cards in deck
        for(int j = 0; j < (int)pinochleHands.size(); j++) {  //repeat for the number of players
            pinochleDeck >> pinochleHands[j]; //deal three cards to player's hand
            pinochleDeck >> pinochleHands[j];
            pinochleDeck >> pinochleHands[j];
        } 
    }
}

//play function
int PinochleGame::play() {
    const int SUCCESS = 0;
    string input;  //declare input variable to store commmand line input
    while(input != "yes") {  //repeat game till user input yes
        pinochleDeck.shuffle();  //shuffle the deck
        deal();  //deal cards to the players
        for(int n=0; n < (int)names.size(); n++) {  //print out players' hands
            cout << names[n] << "'s hand is: " << endl;
            pinochleHands[n].print(cout, PINOCHLE_PRINT);
            cout << endl;
        }
        
        //collect players' hands back to deck
        for(int m=0; m < (int)pinochleHands.size(); m++) {
            pinochleDeck.collect(pinochleHands[m]);
        }
        
        //prompt for user input
        cout << "Do you want to end the game?" << endl;
        cin >> input;
    }

    
    return SUCCESS;
}


