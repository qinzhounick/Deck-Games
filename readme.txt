1. Lab 1
Qinzhou(Nick) Song, Email: qinzhounick@wustl.edu
Xinyu(Jack) Li, Email: l.xinyujack@wustl.edu

2. Design Decisions:
8) We added our own copy constructor because the default copy constructor performs shallow copy
, while we want a deep copy constructor instead.





2. Errors: 
a) We had an error where our play() function in Game was undefined to the compiler.
     We solved this problem by adding Game.h in our Makefile

3. Incorrect output:
a) Our first output was printing cardset is empty nonstop instead of players' hands or the board. 
     It was because in our CardSet operator, we checked if the CardSet passed in was empty.
     When the operator is called in deal() for the first time, for example, pinochleDeck >> pinochleHands[j];
     pinochleHands had empty hands, so c.empty is true and we are stuck in an infinite loop.

Code:
template<typename R, typename S>
CardSet<R,S> & CardSet<R,S>::operator>> (CardSet<R,S> & c) {
    try {
        if(c.empty()) { //check if cards is empty
            throw std::runtime_error("runtime_error"); //throw error
        } else {
            //if not empty, push back last card to another CardSet
            //  and pop the last card
            size_t t = cards.size();
            c.cards.push_back(Card<R, S>(cards[t-1]._rank, cards[t-1]._suit));
            cards.pop_back();
        }
    } catch(std::runtime_error const&) {
        cout << "cardset is empty: " << endl; //print error message
    }
    return *this; 
}

5. Correct output:
HoldEm: supposed to print each player's hand(two cards) and print board for three turns(3 for flop, 4 for turn, 5 for river),
then, promt for user input, if no repeat whole process, if yes end game.

-------Output------------
[qinzhounick@linuxlab007 cse428_lab1]$ ./lab1 HoldEm 1 2 3 4
1's hand is: 5D AS 
2's hand is: 10C 3S 
3's hand is: 10H QD 
4's hand is: 4H 3C 
BOARD(flop):9H QH 5S 
BOARD(turn):9H QH 5S 6H 
BOARD(river):9H QH 5S 6H 4S 
Do you want to end the game?
no
1's hand is: 7S KC 
2's hand is: 8D JC 
3's hand is: 2S 8H 
4's hand is: 3H 5H 
BOARD(flop):3S 6D AS 
BOARD(turn):3S 6D AS QH 
BOARD(river):3S 6D AS QH JH 
Do you want to end the game?
yes
[qinzhounick@linuxlab007 cse428_lab1]$ 


Pinochle: supposed to print each player's hand(12 cards) and promt for user input, if no repeat whole process, if yes end game.

-------Output------------
[qinzhounick@linuxlab007 cse428_lab1]$ ./lab1 Pinochle 1 2 3 4
1's hand is: KS AC 10S 9C JS QH 9S 9S JD 9H 9C 10D 
2's hand is: 9D JH JS KD 10C AH QS KS QD QC 10H AS 
3's hand is: AH AD 10C 9H JH AC 10S 9D JD 10D QS 10H 
4's hand is: KC KH AD QD KC QC QH JC KD JC KH AS 
Do you want to end the game?
no
1's hand is: KS 10H 9D JH 10S QC 10D JC AS QC 9C QD 
2's hand is: AH JH AH AC JS 9H 10C 10C QH KD 9D AC 
3's hand is: KS QD KC JS 10H KD AS QS AD AD JD 10S 
4's hand is: QS 10D KC KH JD 9S 9C JC KH 9H 9S QH 
Do you want to end the game?
yes
[qinzhounick@linuxlab007 cse428_lab1]$ 