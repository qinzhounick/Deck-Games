#include "PinochleGame.h"

PinochleGame::PinochleGame(int argc, const char * argv[]): Game(argc, argv) {
    CardSet<PinochleRank, Suit> playerHand;
    int i = 2;
    for(i; i<argc; i++) {
        pinochleHands.push_back(playerHand); // not completed
    }
}

void PinochleGame::deal() {
    int j = 0;
    while(!pinochleDeck.is_empty()) {
        for(j; j<pinochleHands.size(); j++) {
            pinochleDeck >> pinochleHands[j];
            pinochleDeck >> pinochleHands[j];
            pinochleDeck >> pinochleHands[j];
        } 
    }
}

int PinochleGame::play() {
    const int SUCCESS = 0;
    char *input;
    while(input != "yes") {  // #12 not sure
        pinochleDeck.shuffle();
        deal();
        for(int n=0; n<names.size(); n++) {
            cout << names[n] << "'s hand is: " << endl;
            pinochleHands[n].print(cout, 12);
            cout << endl;
        }

        for(int m=0; m<pinochleHands.size(); m++) {
            pinochleDeck.collect(pinochleHands[m]);
        }
        
        cout << "Do you want to end the game?" << endl;
        cin >> input;
    }
    return SUCCESS;
}


