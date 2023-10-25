//File Name: HoldEmGame.cpp
//Authors: Qinzhou(Nick) Song, Xinyu(Jack) Li
//Email: qinzhounick@wustl.edu, l.xinyujack@wustl.edu
//Summary: source file for HoldEmGame
//  define constructor and functions 

#include "HoldEmGame.h"

using namespace std;

//HoldEmGame constructor
//  construct base class and initialize state
HoldEmGame::HoldEmGame(int argc, const char * argv[]): Game(argc, argv), state(HoldEmState::preflop) {  
    CardSet<HoldEmRank, Suit> playerHand;  //declare empty player hands
    for(int i = INDEX; i<argc; i++) {  //repeat for the number of players given
        holdEmHands.push_back(playerHand);  //push hand to holdEmHands
    }
}


//deal function
void HoldEmGame::deal() {
    switch(state) {  //check the current state
        case HoldEmState::preflop:
            //deal one card to each player and then deal another
            //  each player has two cards in this state
            for(int i = 0; i<(int)holdEmHands.size(); i++) { 
                holdEmDeck >> holdEmHands[i];
            } 
            for(int j = 0; j<(int)holdEmHands.size(); j++) {
                holdEmDeck >> holdEmHands[j];
            } 
            state = HoldEmState::flop;  //update state
            break;
        case HoldEmState::flop:
            // deal three cards to the board
            holdEmDeck >> board;
            holdEmDeck >> board;
            holdEmDeck >> board;
            state = HoldEmState::turn;  //update state
            break;
        case HoldEmState::turn:
            holdEmDeck >> board;  //deal one more card to the board
            state = HoldEmState::river;  //update state
            break;
        case HoldEmState::river:
            holdEmDeck >> board;  //deal one more card to the board
            state = HoldEmState::undefined;  //update state
            break;
        case HoldEmState::undefined:  //undefined state does nothing
            break;
    }
}

//play function
int HoldEmGame::play() {
    string input;  //declare input variable to store commmand line input
    while(input != "yes") {  //repeat game till user input yes
        holdEmDeck.shuffle();  //shuffle the deck
        state = HoldEmState::preflop;  //start from the first state
        deal();  //deal cards to the players
        for(int n=0; n<(int)names.size(); n++) {  //print out players' hands
            cout << names[n] << "'s hand is: ";
            holdEmHands[n].print(cout, 2);
        }

        
        deal();  // deal cards for flop state
        cout << "BOARD(flop):";  //print board
        board.print(cout, FLOP_PRINT);

        vector<HoldEmGame::playerStruct> playerS; //vecotr for player struct
        for(int n=0; n<(int)names.size(); n++) {  //loop through players
            HoldEmGame::playerStruct tmp(holdEmHands[n], names[n], HoldEmHandRank::undefined); //
            playerS.push_back(tmp); //push back player struct
        }
        for(auto x: playerS){  //loop through vector
            board >> x._cardset;  //add cards from board to player cardset
            x._rank = holdem_hand_evaluation(x._cardset);  //set player ranks
        }
        sort(playerS.begin(), playerS.end()); //sort player by rank

        deal();  // deal cards for turn state
        cout << "BOARD(turn):";  //print board
        board.print(cout, TURN_PRINT);

        deal();  // deal cards for river state
        cout << "BOARD(river):";  //print board
        board.print(cout, RIVER_PRINT);

        //collect players' hands back to deck
        for(int m=0; m<(int)holdEmHands.size(); m++) {
            holdEmDeck.collect(holdEmHands[m]);
        }

        //collect cards from board to deck
        holdEmDeck.collect(board);
        
        //prompt for user input
        cout << "Do you want to end the game?" << endl;
        cin >> input;
    }


    return SUCCESS;
}


//left shift operator
std::ostream & operator<< (std::ostream& os, const HoldEmHandRank & hhr) {
    //output all the ranks
    if(hhr==HoldEmHandRank::xhigh){
        os <<  "high card";
    }else if(hhr==HoldEmHandRank::pair){
        os <<  "one pair";
    }else if(hhr==HoldEmHandRank::twopair){
        os <<  "two pair";
    }else if(hhr==HoldEmHandRank::threeofakind){
        os <<  "three of a kind";
    }else if(hhr==HoldEmHandRank::straight){
        os <<  "straight";
    }else if(hhr==HoldEmHandRank::flush){
        os <<  "flush";
    }else if(hhr==HoldEmHandRank::fullhouse){
        os <<  "full house";
    }else if(hhr==HoldEmHandRank::fourofakind){
        os <<  "four of a kind";
    }else if(hhr==HoldEmHandRank::straightflush){
        os <<  "straight flush";
    }else if(hhr==HoldEmHandRank::undefined){
        os <<  "undefined";
    }

    return os;
}

HoldEmHandRank HoldEmGame::holdem_hand_evaluation(const CardSet<HoldEmRank, Suit> & playerHand){
    CardSet<HoldEmRank, Suit> copyHand(playerHand);
    vector<Card<HoldEmRank, Suit> > * cards = CardSet<HoldEmRank, Suit>::getCards(copyHand);
    sort(cards->begin(), cards->end());
    HoldEmRank r1, r2, r3, r4, r5;
    Suit s1, s2, s3, s4, s5;
    r1 = cards->at(0)._rank;
    r2 = cards->at(1)._rank;
    r3 = cards->at(2)._rank;
    r4 = cards->at(3)._rank;
    r5 = cards->at(4)._rank;

    s1 = cards->at(0)._suit;
    s2 = cards->at(1)._suit;
    s3 = cards->at(2)._suit;
    s4 = cards->at(3)._suit;
    s5 = cards->at(4)._suit;

    bool straight;
    if(r1==HoldEmRank::two && r5==HoldEmRank::ace){
        straight = (
            r2 == ++r1 &&
            r3 == ++r1 &&              
            r4 == ++r1
        );
    }else{
        straight = (
            r2 == ++r1 &&
            r3 == ++r1 &&              
            r4 == ++r1 &&
            r5 == ++r1
        );
    }
    bool flush = (
        s1 == s2 && s2 == s3 && s3 == s4 && s4 == s5
    );
    bool straightflush = (straight && flush);

    r1 = cards->at(0)._rank; //reset r1

    bool fourofakind = (
        (r1 == r2 && r2 == r3 && r3 == r4) || (r2 == r3 && r3 == r4 && r4 == r5)
    );

    bool fullhouse = (
        (r1 == r2 && r2 == r3 && r4 == r5) || (r1 == r2 && r3 == r4 && r4 == r5)
    );

    bool threeofakind = (
        (r1 == r2 && r2 == r3) || (r2 == r3 && r3 == r4) || (r3 == r4 && r4 == r5)
    );

    bool twopair = (
        (r1 == r2 && r3 == r4) || (r1 == r2 && r4 == r5) ||
        (r2 == r3 && r4 == r5)
    );
    bool pair = (
        r1 == r2 || r2 == r3 || r3 == r4 || r4 == r5
    );



    if(cards->size() != 5){
        return HoldEmHandRank::undefined;
    }else if(straightflush){
        return HoldEmHandRank::straightflush;
    }else if(fourofakind){
        return HoldEmHandRank::fourofakind;
    }else if(fullhouse){
        return HoldEmHandRank::fullhouse;
    }else if(flush){
        return HoldEmHandRank::flush;
    }else if(straight){
        return HoldEmHandRank::straight;
    }else if(threeofakind){
        return HoldEmHandRank::threeofakind;
    }else if(twopair){
        return HoldEmHandRank::twopair;
    }else if(pair){
        return HoldEmHandRank::pair;
    }

    return HoldEmHandRank::xhigh;
}

//struct constructor
HoldEmGame::playerStruct::playerStruct(CardSet<HoldEmRank, Suit> cardset, std::string & name, HoldEmHandRank rank)
    :_cardset(cardset), _name(name), _rank(rank){}

//less than operator
bool operator< (const HoldEmGame::playerStruct & player1, const HoldEmGame::playerStruct & player2){
    if(player1._rank < player2._rank) return true;

    //get players' hands and sort them
    CardSet<HoldEmRank, Suit> copyHand1(player1._cardset);
    CardSet<HoldEmRank, Suit> copyHand2(player2._cardset);
    auto cards1 = CardSet<HoldEmRank, Suit>::getCards(copyHand1);
    auto cards2 = CardSet<HoldEmRank, Suit>::getCards(copyHand2);
    sort(cards1->begin(), cards1->end());
    sort(cards2->begin(), cards2->end());

    if(player1._rank == player2._rank){
        if(player1._rank == HoldEmHandRank::pair){
            return pair_helper(*cards1, *cards2);
        }
        if(player1._rank == HoldEmHandRank::twopair){
            return twopair_helper(*cards1, *cards2);
        }
        if(player1._rank == HoldEmHandRank::threeofakind || player1._rank == HoldEmHandRank::fullhouse){
            return threeofakindOrFullhouse_helper(*cards1, *cards2);
        }
        if(player1._rank == HoldEmHandRank::straight){
            return straight_helper(*cards1, *cards2);
        }
        if(player1._rank == HoldEmHandRank::flush || player1._rank == HoldEmHandRank::xhigh){
            return flushOrXhigh_helper(*cards1, *cards2);
        }
        if(player1._rank == HoldEmHandRank::fourofakind){
            return fourofakind_helper(*cards1, *cards2);
        }
        if(player1._rank == HoldEmHandRank::straightflush){
            return straightflush_helper(*cards1, *cards2);
        }
    }

    return false;
}

//helper function for straight flush rank
bool straightflush_helper(vector<Card<HoldEmRank, Suit> > player1Cards, vector<Card<HoldEmRank, Suit> > player2Cards){
    int n = player1Cards.size() - 1;
    if(player1Cards[n]._rank < player2Cards[n]._rank) return true;

    return false;
}


//helper function for four of a kind rank
bool fourofakind_helper(vector<Card<HoldEmRank, Suit> > player1Cards, vector<Card<HoldEmRank, Suit> > player2Cards){
    int player1_index, player2_index; //declare indices
    
    //find the indices of the pairs in both players' hands
    for(int i=0; i<(int)player1Cards.size()-2; i++){
        //check player1 cards
        if(player1Cards[i]._rank==player1Cards[i+1]._rank){
            player1_index = i;
        }

        //check player2 cards
        if(player2Cards[i]._rank==player2Cards[i+1]._rank){
            player2_index = i;
        }
    }

    if(player1Cards[player1_index]._rank < player2Cards[player2_index]._rank) return true;

    return false;
}

//helper function for flush or xhigh rank
bool flushOrXhigh_helper(vector<Card<HoldEmRank, Suit> > player1Cards, vector<Card<HoldEmRank, Suit> > player2Cards){
    vector<bool> sameCards{true, false, false, false, false, false};
    int i = player1Cards.size()-1;
    int j = player2Cards.size()-1;
    int k = 1;

    while(i>=0 && j>=0){
        if(player1Cards[i]._rank == player2Cards[j]._rank){
            sameCards[k] = true;
        }else if(player1Cards[i]._rank < player2Cards[j]._rank && sameCards[k-1]){
            return true;
        }

        i--;
        j--;
        k++;
    }

    return false;
}


//helper function for straight rank
bool straight_helper(vector<Card<HoldEmRank, Suit> > player1Cards, vector<Card<HoldEmRank, Suit> > player2Cards){
    int n = player1Cards.size() - 1;
    if(player1Cards[n]._rank < player2Cards[n]._rank) return true;
    if(player1Cards[n]._rank == player2Cards[n]._rank && player1Cards[n]._rank == HoldEmRank::ace){
        if(player1Cards[n-1]._rank < player2Cards[n-1]._rank) return true;
    }

    return false;
}



//helper function for three of a kind and full house rank
bool threeofakindOrFullhouse_helper(vector<Card<HoldEmRank, Suit> > player1Cards, vector<Card<HoldEmRank, Suit> > player2Cards){
    int player1_index, player2_index; //declare indices
    
    //find the indices of the pairs in both players' hands
    for(int i=0; i<(int)player1Cards.size()-2; i++){
        //check player1 cards
        if(player1Cards[i]._rank==player1Cards[i+1]._rank && player1Cards[i]._rank==player1Cards[i+2]._rank){
            player1_index = i;
        }

        //check player2 cards
        if(player2Cards[i]._rank==player2Cards[i+1]._rank && player2Cards[i]._rank==player2Cards[i+2]._rank){
            player2_index = i;
        }
    }

    if(player1Cards[player1_index]._rank < player2Cards[player2_index]._rank) return true;

    return false;
}

//helper function for two pair rank
bool twopair_helper(vector<Card<HoldEmRank, Suit> > player1Cards, vector<Card<HoldEmRank, Suit> > player2Cards){
    int player1_pair1, player1_pair2, player2_pair1, player2_pair2, player1_single_card, player2_single_card; //declare indices
    const int indices_sum = 10;     //variable to help calculating index
    const int twopair_indexing = 2; //variable to help calculating index
    bool player1_found_pair = false; 
    bool player2_found_pair = false;

    //find the indices of the pairs in both players' hands
    for(int i=0; i<(int)player1Cards.size()-1; i++){
        //find player1 pairs
        if(player1Cards[i]._rank==player1Cards[i+1]._rank){
            if(!player1_found_pair){
                player1_pair1 = i;
                player1_found_pair = true;
            }else player1_pair2 = i;
        }

        //find player2 pairs
        if(player2Cards[i]._rank==player2Cards[i+1]._rank){
            if(!player2_found_pair){
                player2_pair1 = i;
                player2_found_pair = true;
            }else player2_pair2 = i;
        }
    }

    //calculate indices of single cards in both players' hands
    player1_single_card = indices_sum - player1_pair1*twopair_indexing - player1_pair2*twopair_indexing - twopair_indexing;
    player2_single_card = indices_sum - player2_pair1*twopair_indexing - player2_pair2*twopair_indexing - twopair_indexing;
    


    if(player1Cards[player1_pair2]._rank < player2Cards[player2_pair2]._rank){ //if player1 higher pair smaller than player2 higher pair
        return true;
    }else if(player1Cards[player1_pair2]._rank == player2Cards[player2_pair2]._rank //if higher pairs are the same
    && player1Cards[player1_pair1]._rank < player2Cards[player2_pair1]._rank){ //if player1 low pair smaller than player2 lower pair
        return true;
    }else if(player1Cards[player1_pair2]._rank == player2Cards[player2_pair2]._rank //if higher and lower pairs are the same
    && player1Cards[player1_pair1]._rank == player2Cards[player2_pair1]._rank){ //if player1 single card smaller than player2 single card
        if(player1Cards[player1_single_card] < player2Cards[player2_single_card]){
            return true;
        }
    }

    return false; //return false otherwise
}

//helper function for one pair rank
bool pair_helper(vector<Card<HoldEmRank, Suit> > player1Cards, vector<Card<HoldEmRank, Suit> > player2Cards){
    int player1_pair_index,  player2_pair_index; //declare indices

    //find the indices of the pairs in both players' hands
    for(int i=0; i<(int)player1Cards.size()-1; i++){
        //check player1 cards
        if(player1Cards[i]._rank==player1Cards[i+1]._rank){
            player1_pair_index = i + 1;
        }

        //check player2 cards
        if(player2Cards[i]._rank==player2Cards[i+1]._rank){
            player2_pair_index = i + 1;
        }
    }

    
    vector<bool> sameCards{true, false, false, false};
    int i = player1Cards.size()-1;
    int j = player2Cards.size()-1;
    int k = 1;

    while(i>=0 && j>=0){
        if(i==player1_pair_index){
            i -= 2;
            if(i<0) break;
        }

        if(j==player2_pair_index){
            j -= 2;
            if(j<0) break;
        }

        if(player1Cards[i]._rank == player2Cards[j]._rank){
            sameCards[k] = true;
        }else if(player1Cards[i]._rank < player2Cards[j]._rank && sameCards[k-1]){
            return true;
        }


        i--;
        j--;
        k++;
    }

    return false;
}


