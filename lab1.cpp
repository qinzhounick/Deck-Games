//File Name: lab1.cpp
//Authors: Qinzhou(Nick) Song, Xinyu(Jack) Li
//Email: qinzhounick@wustl.edu, l.xinyujack@wustl.edu
//Summary: source file for main function and create function

#include "HoldEmGame.h"
#include "PinochleGame.h"
#include <memory>

using namespace std;

//create function to create game
shared_ptr<Game> create(int argc, const char *argv[]) {
    shared_ptr<Game> game;  //declare game shared pointer

    string gameName = argv[1];  //get game name

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
    const int PINOCHLE_ARGC = 6;
    const int HOLDEM_MAX_ARGC = 11;
    const int HOLDEM_MIN_ARGC = 4;

    shared_ptr<Game> p;

    string gameName = argv[1];

    //check for game type
    if((gameName == "Pinochle" && argc == PINOCHLE_ARGC) || (gameName == "HoldEm" && (argc <= HOLDEM_MAX_ARGC && argc >= HOLDEM_MIN_ARGC))) {
        p = create(argc, argv);  //create game 
        if(p){  //check if it's null pointer
            return p->play();  //play game
        } else {
            cout << "Failed to create game." << endl;  //print error message if null pointer
            return FAIL_TO_CREATE;
        }
    } else {
        //print error message for usage
        cout << "Invalid command, please follow the format: <excutable> <gamename> <player1> <player2> ..." << endl;
        return INVALID_INPUT;
    }

    return SUCCESS;
}
