1. Lab 2
Qinzhou(Nick) Song, Email: qinzhounick@wustl.edu
Xinyu(Jack) Li, Email: l.xinyujack@wustl.edu

2. Design Decisions:
Q8) We added our own copy constructor because the default copy constructor performs shallow copy
, while we want a deep copy constructor instead.

Q12) We stored pairs of <string(meld_name), int(points)> into a vector for overloaded shift operator.
Then, we stored all melds card combinations into a vector.(a vector of vectors of cards).
Inside our PinochleGame evaluation function, we used std::set_intersection 
  to check if player hand overlaps with any of the combinations.
If one of combinations is found, we push back into the PinochleMeld vector.
Finally, we print the melds and points from our melds vector in play function.

Q15) For our HoldEmGame evaluation function, we brute-forced to check equalities between cards to find the rank

Q16) For our HoldEmGame operator<, we first returned if rank a < rank b.
If ranks are equal, we used if statement to check what rank they are.
Then, we wrote helper functions for each rank to check if less than 


2. Errors: 
We only had two errors throughout the entire lab, because we thought through our methods clearly, then started programming.
a) We had an undefined reference for our less than operator when we tried to sort cards in CardSet
We realized that we did not have an overloaded less than operator for Card class, so we added one.
Problem was solved.

b) Our playerStruct inside HoldEmGame class had an error message of "...default definition would be ill-formed".
We asked Prof. Gill and found that because we were declaring a std::string reference inside our struct inside the HoldEmGame
, which is not allowed by the compiler. We solved this by making the variable just std::string instead of std::string &.

3. Incorrect output:
a) For the less than operator of HoldEmGame, we did not check the same rank of one pairs to see if which pair is bigger.
So our output had 4S 4D bigger than 9C 9D.

b) For our PinochleGame output, we kept getting random melds for different hands. It was because that we were using an 
    unordered_map to store our <meld_name,int> pair and unordered_map has random access. That's why it was giving us random
    melds. We solved this by storing the pair inside a vector, so we can index into the vector to find the right meld.

c) We had wrong output for one pair ranks:
Player 1's hand: 2S 5C 5S 6D 7C 
Rank: one pair

Player 2's hand: 2S 5D 6D 6S 7C 
Rank: one pair

This was because inside our one pair helper function for less than operator
, we only checked if hand a is less than hand b, and return true. 
But we forgot to check if hand b is less than hand a, and return false.
We added that and it solved problem.

5. Correct output:
HoldEm: supposed to print each player's hand(two cards) and print board for three turns(3 for flop, 4 for turn, 5 for river),
next, print out each player's hand after flop, and determine what rank they have in their hands,
and sort them in descending order by ranks.
Then, prompt for user input, if no repeat whole process, if yes end game.

-------Output------------
[l.xinyujack@linuxlab008 cse428_lab1]$ ./lab2 HoldEm 1 2 3 4
1's hand is: 4C 9D 
2's hand is: 2C 8S 
3's hand is: 9H QH 
4's hand is: 9C QD 

BOARD(flop):2H JH AH 
Player 3's hand: 2H 9H JH QH AH 
Rank: flush

Player 2's hand: 2C 2H 8S JH AH 
Rank: one pair

Player 4's hand: 2H 9C JH QD AH 
Rank: high card

Player 1's hand: 2H 4C 9D JH AH 
Rank: high card

BOARD(turn):2H 10D JH AH 
BOARD(river):2H 4H 10D JH AH 
Do you want to end the game?
no
1's hand is: 9H QD 
2's hand is: 6H AD 
3's hand is: 2C 5H 
4's hand is: 8D KH 

BOARD(flop):3C 7H 8C 
Player 4's hand: 3C 7H 8C 8D KH 
Rank: one pair

Player 2's hand: 3C 6H 7H 8C AD 
Rank: high card

Player 1's hand: 3C 7H 8C 9H QD 
Rank: high card

Player 3's hand: 2C 3C 5H 7H 8C 
Rank: high card

BOARD(turn):3C 7H 8C QH 
BOARD(river):3C 7H 8C JH QH 
Do you want to end the game?
no
1's hand is: 5C KD 
2's hand is: 2D QD 
3's hand is: 6C QS 
4's hand is: 4D 10D 

BOARD(flop):9H 10C KH 
Player 1's hand: 5C 9H 10C KD KH 
Rank: one pair

Player 4's hand: 4D 9H 10C 10D KH 
Rank: one pair

Player 3's hand: 6C 9H 10C QS KH 
Rank: high card

Player 2's hand: 2D 9H 10C QD KH 
Rank: high card

BOARD(turn):9H 9S 10C KH 
BOARD(river):6S 9H 9S 10C KH 
Do you want to end the game?
yes
[l.xinyujack@linuxlab008 cse428_lab1]$ 


Pinochle: supposed to print each player's hand(12 cards) and promt for user input, if no repeat whole process, if yes end game.

-------Output------------
[l.xinyujack@linuxlab008 cse428_lab1]$ ./lab2 Pinochle 1 2 3 4
1's hand is: 9D JC JS QH KD KH KS KS 10C 10D AC AS 
1's Melds: 

2's hand is: 9D 9H 9S JD QD QH KC KD 10C 10H AD AH 
2's Melds: 

3's hand is: 9C 9C 9H 9S JD QC QS KC KH 10S AC AD 
3's Melds: pinochle: 40  

4's hand is: JC JH JH JS QC QD QS 10D 10H 10S AH AS 
4's Melds: 

Do you want to end the game?
no
1's hand is: 9S JH QH KC KS 10D 10D 10H 10S AC AS AS 
1's Melds: 

2's hand is: JC JS JS QC QS KD KD KS 10C 10C AH AH 
2's Melds: 

3's hand is: 9C 9C 9S JC QD QH QS KH 10S AC AD AD 
3's Melds: 

4's hand is: 9D 9D 9H 9H JD JD JH QC QD KC KH 10H 
4's Melds: 

Do you want to end the game?
no
1's hand is: JC JD JD JH QH QS KS 10D 10D 10S AC AS 
1's Melds: pinochle: 40  

2's hand is: 9C 9H 9S JS KC KC KH 10C 10S AD AH AS 
2's Melds: 

3's hand is: 9D 9D JH JS QC QD QD QH QS KD KD AC 
3's Melds: sixtyqueens: 60  

4's hand is: 9C 9H 9S JC QC KH KS 10C 10H 10H AD AH 
4's Melds: 

Do you want to end the game?
no
1's hand is: 9C JH QC QC QS QS KD 10C 10S AC AH AH 
1's Melds: 

2's hand is: 9D 9D 9H 9S QH QH KC KD 10D AC AD AS 
2's Melds: 

3's hand is: 9C 9H JC JD QD QD KC KH 10D 10H 10H 10S 
3's Melds: 

4's hand is: 9S JC JD JH JS JS KH KS KS 10C AD AS 
4's Melds: fortyjacks: 40  

Do you want to end the game?
yes
[l.xinyujack@linuxlab008 cse428_lab1]$ 