//File Name: HoldEmGame.cpp
//Authors: Qinzhou(Nick) Song, Xinyu(Jack) Li
//Email: qinzhounick@wustl.edu, l.xinyujack@wustl.edu
//Summary: source file for HoldEmGame
//  define constructor and functions 

#include "HoldEmGame.h"

using namespace std;

//HoldEmGame constructor
//  construct base class and initialize state
HoldEmGame::HoldEmGame(int argc, const char * argv[]): Game(argc, argv), state(HoldEmState::preflop) {  
    CardSet<HoldEmRank, Suit> playerHand;  //declare empty player hands
    for(int i = INDEX; i<argc; i++) {  //repeat for the number of players given
        holdEmHands.push_back(playerHand);  //push hand to holdEmHands
    }
}

//deal function
void HoldEmGame::deal() {
    switch(state) {  //check the current state
        case HoldEmState::preflop:
            //deal one card to each player and then deal another
            //  each player has two cards in this state
            for(int i = 0; i<(int)holdEmHands.size(); i++) { 
                holdEmDeck >> holdEmHands[i];
            } 
            for(int j = 0; j<(int)holdEmHands.size(); j++) {
                holdEmDeck >> holdEmHands[j];
            } 
            state = HoldEmState::flop;  //update state
            break;
        case HoldEmState::flop:
            // deal three cards to the board
            holdEmDeck >> board;
            holdEmDeck >> board;
            holdEmDeck >> board;
            state = HoldEmState::turn;  //update state
            break;
        case HoldEmState::turn:
            holdEmDeck >> board;  //deal one more card to the board
            state = HoldEmState::river;  //update state
            break;
        case HoldEmState::river:
            holdEmDeck >> board;  //deal one more card to the board
            state = HoldEmState::undefined;  //update state
            break;
        case HoldEmState::undefined:  //undefined state does nothing
            break;
    }
}

//play function
int HoldEmGame::play() {
    string input;  //declare input variable to store commmand line input
    while(input != "yes") {  //repeat game till user input yes
        holdEmDeck.shuffle();  //shuffle the deck
        state = HoldEmState::preflop;  //start from the first state
        deal();  //deal cards to the players
        for(int n=0; n<(int)names.size(); n++) {  //print out players' hands
            cout << names[n] << "'s hand is: ";
            holdEmHands[n].print(cout, 2);
        }

        
        deal();  // deal cards for flop state
        cout << "BOARD(flop):";  //print board
        board.print(cout, FLOP_PRINT);

        deal();  // deal cards for turn state
        cout << "BOARD(turn):";  //print board
        board.print(cout, TURN_PRINT);

        deal();  // deal cards for river state
        cout << "BOARD(river):";  //print board
        board.print(cout, RIVER_PRINT);

        //collect players' hands back to deck
        for(int m=0; m<(int)holdEmHands.size(); m++) {
            holdEmDeck.collect(holdEmHands[m]);
        }

        //collect cards from board to deck
        holdEmDeck.collect(board);
        
        //prompt for user input
        cout << "Do you want to end the game?" << endl;
        cin >> input;
    }


    return SUCCESS;
}


