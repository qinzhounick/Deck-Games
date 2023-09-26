#include "PinochleGame.h"

PinochleGame::PinochleGame(int argc, const char * argv[]): Game(argc, argv) {
    CardSet<PinochleRank, Suit> playerHand;
    for(int i = 2; i<argc; i++) {
        pinochleHands.push_back(playerHand); // not completed
    }
}

void PinochleGame::deal() {
    while(!pinochleDeck.is_empty()) {
        for(int j = 0; j < (int)pinochleHands.size(); j++) {
            pinochleDeck >> pinochleHands[j];
            pinochleDeck >> pinochleHands[j];
            pinochleDeck >> pinochleHands[j];
        } 
    }
}

int PinochleGame::play() {
    const int SUCCESS = 0;
    string input;
    while(input != "yes") {  // #12 not sure
        pinochleDeck.shuffle();
        deal();
        for(int n=0; n < (int)names.size(); n++) {
            cout << names[n] << "'s hand is: " << endl;
            pinochleHands[n].print(cout, 12);
            cout << endl;
        }

        for(int m=0; m < (int)pinochleHands.size(); m++) {
            pinochleDeck.collect(pinochleHands[m]);
        }
        
        cout << "Do you want to end the game?" << endl;
        cin >> input;
    }
    return SUCCESS;
}


