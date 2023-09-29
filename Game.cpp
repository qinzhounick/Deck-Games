//File Name: Game.cpp
//Authors: Qinzhou(Nick) Song, Xinyu(Jack) Li
//Email: qinzhounick@wustl.edu, l.xinyujack@wustl.edu
//Summary: source file for Game
//  define Game class constructor

#include "Game.h"

using namespace std;

//store player names from commandline arguments
//  to vector names
Game::Game(int argc, const char *argv[]) {
    for(int i = 2; i<argc; i++) {
        names.push_back(argv[i]);
    }
}