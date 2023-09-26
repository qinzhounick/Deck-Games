#include "HoldEmGame.h"
#include "PinochleGame.h"
#include <memory>

using namespace std;

shared_ptr<Game> create(int argc, const char *argv[]) {
    shared_ptr<Game> game;

    if(argv[1] == "Pinochle") {
        game = make_shared<PinochleGame>(argc, argv);
    } else if (argv[1] == "HoldEm") {
        game = make_shared<HoldEmGame>(argc, argv);
    }
    return game;
}

int main(int argc, const char *argv[]) {

    const int INVALID_INPUT = 1;
    const int FAIL_TO_CREATE = 2;
    shared_ptr<Game> p;

    if((argv[1] == "Pinochle" && argc == 6) || (argv[1] == "HoldEm" && (argc <= 11 && argc >= 4))) {
        p = create(argc, argv);
        if(p){
            return p->play();
        } else {
            cout << "Failed to create game." << endl;
            return FAIL_TO_CREATE;
        }
    } else {
        cout << "Invalid command, please follow the format: <excutable> <gamename> <player1> <player2> ..." << endl;
        return INVALID_INPUT;
    }

    return SUCCESS;
}
