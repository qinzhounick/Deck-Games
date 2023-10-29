//File Name: lab2.cpp
//Authors: Qinzhou(Nick) Song, Xinyu(Jack) Li
//Email: qinzhounick@wustl.edu, l.xinyujack@wustl.edu
//Summary: source file for main function and create function

#include "HoldEmGame.h"
#include "PinochleGame.h"
#include <memory>

using namespace std;
const int GAME_NAME = 1;
//create function to create game
shared_ptr<Game> create(int argc, const char *argv[]) {
    shared_ptr<Game> game;  //declare game shared pointer

    string gameName = argv[GAME_NAME];  //get game name

    //pass game objects to the game shared pointer
    if(gameName == "Pinochle") {
        game = make_shared<PinochleGame>(argc, argv);
    } else if (gameName == "HoldEm") {
        game = make_shared<HoldEmGame>(argc, argv);
    }
    return game;
}

int main(int argc, const char *argv[]) {
    //Const int
    const int INVALID_INPUT = 1;
    const int FAIL_TO_CREATE = 2;
    const int NO_GAME_NAME = 3;
    const int PINOCHLE_ARGC = 6;
    const int HOLDEM_MAX_ARGC = 11;
    const int HOLDEM_MIN_ARGC = 4;

    shared_ptr<Game> p;

    if(argc==1){
        cout << "Please provide the game name you wanna play." << endl;
        return NO_GAME_NAME;
    }
    string gameName = argv[GAME_NAME];

    //check for game type
    if((gameName == "Pinochle" && argc == PINOCHLE_ARGC) || (gameName == "HoldEm" && (argc <= HOLDEM_MAX_ARGC && argc >= HOLDEM_MIN_ARGC))) {
        p = create(argc, argv);  //create game 
        if(p){  //check if it's null pointer
            return p->play();  //play game
        } else {
            cout << "Failed to create game." << endl;  //print error message if null pointer
            return FAIL_TO_CREATE;
        }
    // If the game name is correct, check for the player input
    }else if(gameName == "Pinochle" && argc != PINOCHLE_ARGC){
        cout << "Invalid players! Pinochle game takes four players. Please try again." << endl;
        return INVALID_INPUT;
    }else if(gameName == "HoldEm" && (argc > HOLDEM_MAX_ARGC || argc < HOLDEM_MIN_ARGC)){
        cout << "Invalid players! HoldEm game takes 4-11 players. Please try again." << endl;
        return INVALID_INPUT;
    }else {
        //print error message for usage
        cout << "Invalid command, please follow the format: <excutable> <gamename> <player1> <player2> ..." << endl;
        return INVALID_INPUT;
    }

    return SUCCESS;
}
