//File Name: PinochleGame.cpp
//Authors: Qinzhou(Nick) Song, Xinyu(Jack) Li
//Email: qinzhounick@wustl.edu, l.xinyujack@wustl.edu
//Summary: source file for PinochleGame
//  define constructor and functions 

#include "PinochleGame.h"

using namespace std;

// a vector with all pinocle melds with their corresponding points
vector<pair<string, int> > PinochleGame::points = {
    {"dix",10}, {"offsuitmarriage",20},{"fortyjacks", 40}, {"pinochle", 40}, 
    {"insuitmarriage",40}, {"sixtyqueens", 60}, {"eightykings", 80}, {"hundredaces", 100}, 
    {"insuitrun", 150}, {"doublepinochle", 300}, {"fourhundredjacks", 400}, {"sixhundredqueens", 600}, 
    {"eighthundredkings", 600}, {"thousandaces", 1000}, {"insuitdoublerun", 1500}
};
//PinochleGame constructor
//  construct base class and initialize state
PinochleGame::PinochleGame(int argc, const char * argv[]): Game(argc, argv) {
    CardSet<PinochleRank, Suit> playerHand;  //declare empty player hands
    for(int i = INDEX; i<argc; i++) {  //repeat for the number of players given
        pinochleHands.push_back(playerHand);  //push hand to pinochleHands
    }
}

//deal function
void PinochleGame::deal() {
    while(!pinochleDeck.is_empty()) {  //deal all the cards in deck
        for(int j = 0; j < (int)pinochleHands.size(); j++) {  //repeat for the number of players
            pinochleDeck >> pinochleHands[j]; //deal three cards to player's hand
            pinochleDeck >> pinochleHands[j];
            pinochleDeck >> pinochleHands[j];
        } 
    }
}

//play function
int PinochleGame::play() {
    const int SUCCESS = 0;
    string input;  //declare input variable to store commmand line input
    while(input != "yes") {  //repeat game till user input yes
        pinochleDeck.shuffle();  //shuffle the deck
        deal();  //deal cards to the players
        for(int n=0; n < (int)names.size(); n++) {  //print out players' hands
            cout << names[n] << "'s hand is: ";
            pinochleHands[n].print(cout, PINOCHLE_PRINT);
            vector<PinochleMelds> melds;
            suit_independent_evaluation(pinochleHands[n], melds);
            cout << names[n] << "'s Melds: ";
            for(auto x: melds){
                cout << x;
            }
            cout << '\n' << '\n';
        }

        //collect players' hands back to deck
        for(int m=0; m < (int)pinochleHands.size(); m++) {
            pinochleDeck.collect(pinochleHands[m]);
        }
        
        //prompt for user input
        cout << "Do you want to end the game?" << endl;
        cin >> input;
    }

    
    return SUCCESS;
}


//define operator<< for PinochleGame
ostream & operator<< (ostream& os, const PinochleMelds & pm) {
    int _points = static_cast<int>(pm);
    vector<pair<string, int> >::iterator it;
    it= PinochleGame::points.begin();
    advance(it, _points);
    os << it->first << ": " << it->second << "  ";
    return os;
}

// suit_independent_evaluation function to check what combinations players' hands have
void PinochleGame::suit_independent_evaluation(const CardSet<PinochleRank,Suit> & playerHand, vector<PinochleMelds> & melds){
    CardSet<PinochleRank, Suit> copyHand(playerHand);
    vector<Card<PinochleRank, Suit> > * cards = CardSet<PinochleRank, Suit>::getCards(copyHand);

    std::sort(cards->begin(), cards->end()); // sort player's hand in ascending order

    // a vector with all possible combinations
    vector<vector<Card<PinochleRank, Suit> > > combinations = {
        {
        Card<PinochleRank, Suit>(PinochleRank::ace, Suit::clubs), 
        Card<PinochleRank, Suit>(PinochleRank::ace, Suit::clubs),
        Card<PinochleRank, Suit>(PinochleRank::ace, Suit::diamonds), 
        Card<PinochleRank, Suit>(PinochleRank::ace, Suit::diamonds),
        Card<PinochleRank, Suit>(PinochleRank::ace, Suit::hearts), 
        Card<PinochleRank, Suit>(PinochleRank::ace, Suit::hearts),
        Card<PinochleRank, Suit>(PinochleRank::ace, Suit::spades), 
        Card<PinochleRank, Suit>(PinochleRank::ace, Suit::spades)
        },
        {
        Card<PinochleRank, Suit>(PinochleRank::ace, Suit::clubs),
        Card<PinochleRank, Suit>(PinochleRank::ace, Suit::diamonds),
        Card<PinochleRank, Suit>(PinochleRank::ace, Suit::hearts),
        Card<PinochleRank, Suit>(PinochleRank::ace, Suit::spades)
        },
        {
        Card<PinochleRank, Suit>(PinochleRank::king, Suit::clubs), 
        Card<PinochleRank, Suit>(PinochleRank::king, Suit::clubs),
        Card<PinochleRank, Suit>(PinochleRank::king, Suit::diamonds), 
        Card<PinochleRank, Suit>(PinochleRank::king, Suit::diamonds),
        Card<PinochleRank, Suit>(PinochleRank::king, Suit::hearts), 
        Card<PinochleRank, Suit>(PinochleRank::king, Suit::hearts),
        Card<PinochleRank, Suit>(PinochleRank::king, Suit::spades), 
        Card<PinochleRank, Suit>(PinochleRank::king, Suit::spades)
        },
        {
        Card<PinochleRank, Suit>(PinochleRank::king, Suit::clubs),
        Card<PinochleRank, Suit>(PinochleRank::king, Suit::diamonds),
        Card<PinochleRank, Suit>(PinochleRank::king, Suit::hearts),
        Card<PinochleRank, Suit>(PinochleRank::king, Suit::spades)
        },
        {
        Card<PinochleRank, Suit>(PinochleRank::queen, Suit::clubs), 
        Card<PinochleRank, Suit>(PinochleRank::queen, Suit::clubs),
        Card<PinochleRank, Suit>(PinochleRank::queen, Suit::diamonds), 
        Card<PinochleRank, Suit>(PinochleRank::queen, Suit::diamonds),
        Card<PinochleRank, Suit>(PinochleRank::queen, Suit::hearts), 
        Card<PinochleRank, Suit>(PinochleRank::queen, Suit::hearts),
        Card<PinochleRank, Suit>(PinochleRank::queen, Suit::spades), 
        Card<PinochleRank, Suit>(PinochleRank::queen, Suit::spades)
        },
        {
        Card<PinochleRank, Suit>(PinochleRank::queen, Suit::clubs),
        Card<PinochleRank, Suit>(PinochleRank::queen, Suit::diamonds),
        Card<PinochleRank, Suit>(PinochleRank::queen, Suit::hearts),
        Card<PinochleRank, Suit>(PinochleRank::queen, Suit::spades)
        },
        {
        Card<PinochleRank, Suit>(PinochleRank::jack, Suit::clubs), 
        Card<PinochleRank, Suit>(PinochleRank::jack, Suit::clubs),
        Card<PinochleRank, Suit>(PinochleRank::jack, Suit::diamonds), 
        Card<PinochleRank, Suit>(PinochleRank::jack, Suit::diamonds),
        Card<PinochleRank, Suit>(PinochleRank::jack, Suit::hearts), 
        Card<PinochleRank, Suit>(PinochleRank::jack, Suit::hearts),
        Card<PinochleRank, Suit>(PinochleRank::jack, Suit::spades), 
        Card<PinochleRank, Suit>(PinochleRank::jack, Suit::spades)
        },
        {
        Card<PinochleRank, Suit>(PinochleRank::jack, Suit::clubs),
        Card<PinochleRank, Suit>(PinochleRank::jack, Suit::diamonds),
        Card<PinochleRank, Suit>(PinochleRank::jack, Suit::hearts),
        Card<PinochleRank, Suit>(PinochleRank::jack, Suit::spades)
        },
        {
        Card<PinochleRank, Suit>(PinochleRank::jack, Suit::diamonds), 
        Card<PinochleRank, Suit>(PinochleRank::jack, Suit::diamonds),
        Card<PinochleRank, Suit>(PinochleRank::queen, Suit::spades),
        Card<PinochleRank, Suit>(PinochleRank::queen, Suit::spades),
        },
        {
        Card<PinochleRank, Suit>(PinochleRank::jack, Suit::diamonds), 
        Card<PinochleRank, Suit>(PinochleRank::queen, Suit::spades),
        }
    };

    // use intersection of sorted player's hand and the vector of possible combinations
    // to check what melds player has and push them back to melds
    for(int i = 0; i<(int)combinations.size();i++){
        std::vector<Card<PinochleRank, Suit> > intersection;
        std::set_intersection(combinations[i].begin(), combinations[i].end(), cards->begin(), cards->end(), std::back_inserter(intersection));

        if(combinations[i]==intersection){
            switch(i){
                case 0:
                    melds.push_back(PinochleMelds::thousandaces);
                    break;
                case 1:
                    if(std::find(melds.begin(), melds.end(), PinochleMelds::thousandaces) != melds.end()) break;
                    melds.push_back(PinochleMelds::hundredaces);
                    break;
                case 2:
                    melds.push_back(PinochleMelds::eighthundredkings);
                    break;
                case 3:
                    if(std::find(melds.begin(), melds.end(), PinochleMelds::eighthundredkings) != melds.end()) break;
                    melds.push_back(PinochleMelds::eightykings);
                    break;
                case 4:
                    melds.push_back(PinochleMelds::sixhundredqueens);
                    break;
                case 5:
                    if(std::find(melds.begin(), melds.end(), PinochleMelds::sixhundredqueens) != melds.end()) break;
                    melds.push_back(PinochleMelds::sixtyqueens);
                    break;
                case 6:
                    melds.push_back(PinochleMelds::fourhundredjacks);
                    break;
                case 7:
                    if(std::find(melds.begin(), melds.end(), PinochleMelds::fourhundredjacks) != melds.end()) break;
                    melds.push_back(PinochleMelds::fortyjacks);
                    break;
                case 8:
                    melds.push_back(PinochleMelds::doublepinochle);
                    break;
                case 9:
                    if(std::find(melds.begin(), melds.end(), PinochleMelds::doublepinochle) != melds.end()) break;
                    melds.push_back(PinochleMelds::pinochle);
                    break;

            }
        }
    }
    
}


