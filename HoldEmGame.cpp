#include "HoldEmGame.h"

HoldEmGame::HoldEmGame(int argc, const char * argv[]): Game(argc, argv), state(HoldEmState::preflop) {
    CardSet<HoldEmRank, Suit> playerHand;
    int i = 2;
    for(i; i<argc; i++) {
        holdEmHands.push_back(playerHand); // not completed
    }
}

void HoldEmGame::deal() {
    switch(state) {
        case HoldEmState::preflop:
            for(int i = 0; i<holdEmHands.size(); i++) {
                holdEmDeck >> holdEmHands[i];
            } 
            for(int j = 0; j<holdEmHands.size(); j++) {
                holdEmDeck >> holdEmHands[j];
            } 
            state = HoldEmState::flop;
            break;
        case HoldEmState::flop:
            holdEmDeck >> board;
            holdEmDeck >> board;
            holdEmDeck >> board;
            state = HoldEmState::turn;
            break;
        case HoldEmState::turn:
            holdEmDeck >> board;
            state = HoldEmState::river;
            break;
        case HoldEmState::river:
            holdEmDeck >> board;
            state = HoldEmState::undefined;
            break;
        case HoldEmState::undefined:
            break;
    }
}

int HoldEmGame::play() {
    const int SUCCESS = 0;
    char *input;
    while(input != "yes") {  // #12 not sure
        holdEmDeck.shuffle();
        state = HoldEmState::preflop;
        deal();
        for(int n=0; n<names.size(); n++) {
            cout << names[n] << "'s hand is: " << endl;
            holdEmHands[n].print(cout, 2);
            cout << endl;
        }

        deal();
        cout << "BOARD(flop):" << endl;
        board.print(cout, 5);
        cout << endl;

        deal();
        cout << "BOARD(turn):" << endl;
        board.print(cout, 5);
        cout << endl;

        deal();
        cout << "BOARD(river):" << endl;
        board.print(cout, 5);
        cout << endl;

        for(int m=0; m<holdEmHands.size(); m++) {
            holdEmDeck.collect(holdEmHands[m]);
        }

        holdEmDeck.collect(board);
        
        cout << "Do you want to end the game?" << endl;
        cin >> input;
    }
    return SUCCESS;
}


