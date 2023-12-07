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
            holdEmHands[n].print(cout, HOLDEM_HAND_LEN);
        }
        cout << '\n';

        
        deal();  // deal cards for flop state
        cout << "BOARD(flop):";  //print board
        board.print(cout, FLOP_PRINT);

        vector<HoldEmGame::playerStruct> playerS; //vecotr for player struct
        for(int n=0; n<(int)names.size(); n++) {  //loop through players
            HoldEmGame::playerStruct tmp(holdEmHands[n], names[n], HoldEmHandRank::undefined); //
            playerS.push_back(tmp); //push back player struct
        }
        cout << "before the for loop point" << endl;
        for(HoldEmGame::playerStruct & x: playerS){  //loop through vector
            auto boardCards= board.begin();
            x._cardset.add_card(*boardCards++);
            x._cardset.add_card(*boardCards++);
            x._cardset.add_card(*boardCards);
            x._rank = holdem_hand_evaluation(x._cardset);  //set player ranks
        }
        std::sort(playerS.begin(), playerS.end()); //sort player by rank
        for(int i=playerS.size() - NULL_VALUE; i >= 0; i --){  //loop through vector
            cout << "Player " << playerS[i]._name << "'s hand: ";
            playerS[i]._cardset.print(cout, 5);
            cout << "Rank: " << playerS[i]._rank << '\n' << '\n';
        }

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

// define holdem_hand_evaluation function to check what combinations players' hands have
HoldEmHandRank HoldEmGame::holdem_hand_evaluation(const CardSet<HoldEmRank, Suit> & playerHand){
    CardSet<HoldEmRank, Suit> copyHand(playerHand);
    //vector<Card<HoldEmRank, Suit> > * cards = CardSet<HoldEmRank, Suit>::getCards(copyHand);
    vector<Card<HoldEmRank, Suit> > cards;
    //std::copy(copyHand.begin(), copyHand.end(), cards.begin()); //copy the cards into the empty vector
    auto itr1 = copyHand.begin();
    cards.push_back(*itr1++);
    cards.push_back(*itr1++);
    cards.push_back(*itr1++);
    cards.push_back(*itr1++);
    cards.push_back(*itr1);
    sort(copyHand.begin(), copyHand.end()); // sort the player's hand in ascending order
    // copy the rank and suit of each card
    HoldEmRank r1, r2, r3, r4, r5;
    Suit s1, s2, s3, s4, s5;
    auto it = copyHand.begin();
    r1 = it->_rank; s1 = it->_suit; it++; //get the cards' rank and suit by value
    r2 = it->_rank; s2 = it->_suit; it++;
    r3 = it->_rank; s3 = it->_suit; it++;
    r4 = it->_rank; s4 = it->_suit; it++;
    r5 = it->_rank; s5 = it->_suit;

    // check for straight
    bool straight;
    // speical case when ace is the smallest but it is in the last position in the hand
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
    // check for flush
    bool flush = (
        s1 == s2 && s2 == s3 && s3 == s4 && s4 == s5
    );
    // check for straightflush
    bool straightflush = (straight && flush);

    auto itr = copyHand.begin();
    r1 = itr->_rank; //reset r1

    // check for fourofakind
    bool fourofakind = (
        (r1 == r2 && r2 == r3 && r3 == r4) || (r2 == r3 && r3 == r4 && r4 == r5)
    );

    // check for fullhouse
    bool fullhouse = (
        (r1 == r2 && r2 == r3 && r4 == r5) || (r1 == r2 && r3 == r4 && r4 == r5)
    );

    // check for threeofakind
    bool threeofakind = (
        (r1 == r2 && r2 == r3) || (r2 == r3 && r3 == r4) || (r3 == r4 && r4 == r5)
    );

    // check for twopair
    bool twopair = (
        (r1 == r2 && r3 == r4) || (r1 == r2 && r4 == r5) ||
        (r2 == r3 && r4 == r5)
    );

    //check for pair
    bool pair = (
        r1 == r2 || r2 == r3 || r3 == r4 || r4 == r5
    );

    // return appropriate rank
    if(cards.size() != 5){
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
HoldEmGame::playerStruct::playerStruct(CardSet<HoldEmRank, Suit> cardset, std::string name, HoldEmHandRank rank)
    :_cardset(cardset), _name(name), _rank(rank){}

//less than operator
bool operator< (const HoldEmGame::playerStruct & player1, const HoldEmGame::playerStruct & player2){
    if(player1._rank < player2._rank) return true;

    //get players' hands and sort them
    CardSet<HoldEmRank, Suit> copyHand1(player1._cardset);
    CardSet<HoldEmRank, Suit> copyHand2(player2._cardset);

    //create empty vectors of cards to store the hands
    vector<Card<HoldEmRank, Suit> > cards1;
    vector<Card<HoldEmRank, Suit> > cards2;

    auto itr1 = copyHand1.begin();
    cards1.push_back(*itr1++);
    cards1.push_back(*itr1++);
    cards1.push_back(*itr1++); 
    cards1.push_back(*itr1++);
    cards1.push_back(*itr1);

    auto itr2 = copyHand2.begin();
    cards2.push_back(*itr2++);
    cards2.push_back(*itr2++);
    cards2.push_back(*itr2++); 
    cards2.push_back(*itr2++);
    cards2.push_back(*itr2);

    //sort the cards of player1 and player2
    sort(cards1.begin(), cards1.end());
    sort(cards2.begin(), cards2.end());

    
    // call corresponding helper functions regarding the rank
    if(player1._rank == player2._rank){
        if(player1._rank == HoldEmHandRank::pair){
            return pair_helper(cards1, cards2);
        }
        if(player1._rank == HoldEmHandRank::twopair){
            return twopair_helper(cards1, cards2);
        }
        if(player1._rank == HoldEmHandRank::threeofakind || player1._rank == HoldEmHandRank::fullhouse){
            return threeofakindOrFullhouse_helper(cards1, cards2);
        }
        if(player1._rank == HoldEmHandRank::straight){
            return straight_helper(cards1, cards2);
        }
        if(player1._rank == HoldEmHandRank::flush || player1._rank == HoldEmHandRank::xhigh){
            return flushOrXhigh_helper(cards1, cards2);
        }
        if(player1._rank == HoldEmHandRank::fourofakind){
            return fourofakind_helper(cards1, cards2);
        }
        if(player1._rank == HoldEmHandRank::straightflush){
            return straightflush_helper(cards1, cards2);
        }
    }

    return false;
}

//helper function for straight flush rank
bool straightflush_helper(vector<Card<HoldEmRank, Suit> > player1Cards, vector<Card<HoldEmRank, Suit> > player2Cards){
    int n = player1Cards.size() - NULL_VALUE;
    if(player1Cards[n]._rank < player2Cards[n]._rank) return true;

    return false;
}


//helper function for four of a kind rank
bool fourofakind_helper(vector<Card<HoldEmRank, Suit> > player1Cards, vector<Card<HoldEmRank, Suit> > player2Cards){
    int player1_index, player2_index; //declare indices
    
    //find the indices of the pairs in both players' hands
    for(int i=0; i<(int)player1Cards.size() - HOLDEM_HAND_LEN; i++){
        //check player1 cards
        if(player1Cards[i]._rank==player1Cards[i + NEIGHBOR_CARD]._rank){
            player1_index = i;
        }

        //check player2 cards
        if(player2Cards[i]._rank==player2Cards[i + NEIGHBOR_CARD]._rank){
            player2_index = i;
        }
    }

    if(player1Cards[player1_index]._rank < player2Cards[player2_index]._rank) return true;

    return false;
}

//helper function for flush or xhigh rank
bool flushOrXhigh_helper(vector<Card<HoldEmRank, Suit> > player1Cards, vector<Card<HoldEmRank, Suit> > player2Cards){
    // boolean vector showing the comparison result of the card at the same location in two players' hands
    vector<bool> sameCards{true, false, false, false, false, false};
    // going from the last card to the first card
    int i = player1Cards.size()-NULL_VALUE;
    int j = player2Cards.size()-NULL_VALUE;
    int k = 1; // index for the boolean vector

    // compare each card's rank
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
    int n = player1Cards.size() - NULL_VALUE;
    if(player1Cards[n]._rank < player2Cards[n]._rank) return true;
    if(player1Cards[n]._rank == player2Cards[n]._rank && player1Cards[n]._rank == HoldEmRank::ace){
        if(player1Cards[n-NEIGHBOR_CARD]._rank < player2Cards[n-NEIGHBOR_CARD]._rank) return true;
    }

    return false;
}



//helper function for three of a kind and full house rank
bool threeofakindOrFullhouse_helper(vector<Card<HoldEmRank, Suit> > player1Cards, vector<Card<HoldEmRank, Suit> > player2Cards){
    int player1_index, player2_index; //declare indices
    
    //find the indices of the pairs in both players' hands
    for(int i=0; i<(int)player1Cards.size()-HOLDEM_HAND_LEN; i++){
        //check player1 cards
        if(player1Cards[i]._rank==player1Cards[i+NEIGHBOR_CARD]._rank && player1Cards[i]._rank==player1Cards[i+HOLDEM_HAND_LEN]._rank){
            player1_index = i;
        }

        //check player2 cards
        if(player2Cards[i]._rank==player2Cards[i+NEIGHBOR_CARD]._rank && player2Cards[i]._rank==player2Cards[i+HOLDEM_HAND_LEN]._rank){
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
    for(int i=0; i<(int)player1Cards.size()-NULL_VALUE; i++){
        //find player1 pairs
        if(player1Cards[i]._rank==player1Cards[i+NEIGHBOR_CARD]._rank){
            if(!player1_found_pair){
                player1_pair1 = i;
                player1_found_pair = true;
            }else player1_pair2 = i;
        }

        //find player2 pairs
        if(player2Cards[i]._rank==player2Cards[i+NEIGHBOR_CARD]._rank){
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
    for(int i=0; i<(int)player1Cards.size()-NULL_VALUE; i++){
        //check player1 cards
        if(player1Cards[i]._rank==player1Cards[i+NEIGHBOR_CARD]._rank){
            player1_pair_index = i + NEIGHBOR_CARD;
        }

        //check player2 cards
        if(player2Cards[i]._rank==player2Cards[i+NEIGHBOR_CARD]._rank){
            player2_pair_index = i + NEIGHBOR_CARD;
        }
    }

    // compare the one pair rank of two players
    if(player1Cards[player1_pair_index]._rank < player2Cards[player2_pair_index]._rank){
        return true; 
    }else if(player1Cards[player1_pair_index]._rank > player2Cards[player2_pair_index]._rank){
        return false;
    }
 
    // going in order to compare thr rest three single cards  
    vector<bool> sameCards{true, false, false, false};
    // checking from the last card to the first card in players' hands
    int i = player1Cards.size()-NULL_VALUE; 
    int j = player2Cards.size()-NULL_VALUE;
    int k = 1;
    while(i>=0 && j>=0){
        // skip the pair
        if(i==player1_pair_index){
            i -= HOLDEM_HAND_LEN;
            if(i<0) break;
        }
        // skip the pair
        if(j==player2_pair_index){
            j -= HOLDEM_HAND_LEN;
            if(j<0) break;
        }
        // if two single cards at the same location in two players' hands have the same rank, 
        // give true to the location in the vector as a method to skip it in the future
        if(player1Cards[i]._rank == player2Cards[j]._rank){
            sameCards[k] = true;
        // find the single card that determine which player wins over the other
        }else if(player1Cards[i]._rank < player2Cards[j]._rank && sameCards[k-1]){
            return true;
        }

        // after each check, going back one location in the players' hands
        i--;
        j--;
        // aftere each check, going to the next location in the boolean vector,
        // representing the result of each comparison
        k++;
    }

    return false;
}


