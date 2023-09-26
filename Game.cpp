#include "Game.h"

using namespace std;

Game::Game(int argc, const char *argv[]) {
    int i = 2;
    for(i; i<argc; i++) {
        names.push_back(argv[i]);
    }
};