#include "Game.h"

using namespace std;

Game::Game(int argc, const char *argv[]) {
    for(int i = 2; i<argc; i++) {
        names.push_back(argv[i]);
    }
}