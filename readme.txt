1. Lab 0
Qinzhou(Nick) Song, Email: qinzhounick@wustl.edu
Xinyu(Jack) Li, Email: l.xinyujack@wustl.edu

2. Errors:
a)The main error that we had was the ambigeous operator <<. 
  Our shift operator for Card was declared as template<typename C> ostream & operator<< (ostream & os, const C &card);
  This was causing error because the compiler does not know what C is. When we tried to do "os << ' ' ", 
  the compiler was having hard time choosing the right operator<<

We fixed this error by using Card<r,s> as a parameter type for the shift operator for Card. 
  This specifies the type of card that we want to pass by the shift operator.

b) We also had an error of undefined reference of the class default constructor for both PinochleDeck and HoldEmDeck.
    This was because that we did not define a constructor for PinochleDeck with PinochleRank and Suit(same for HoldEmDeck).

We solved this problem by adding the line "template class PinochleDeck<PinochleRank, Suit>;" at the end of PinochleDeck.cpp
  Once we did that, the compiler is aware of the declaration of class PinochleDeck with PinochleRank and Suit types. 
  It will then use the defined constructor inside PinochleDeck.cpp.

3. Incorrect output:
a) Our first output had segmatation fault because we forgot to use switch statement for the prefix operator++.

We fixed this error by using the knowledge we learned from studio2 and fixed the prefix operator++

b) Our second output printed out the cards but in bad format. 
  This was because that we added a line "os << endl" at the end of the operator<< in PinochleDeck and HoldEmDeck.

We fixed it by removing that line.

4. Design decisions:
print(for both Pinochle and HoldEm): we decided to print new line for every rank. Essentially, for each deck, 
  we print out all valid suits for one rank and then move on to the next rank. For instance, PinochleDeck has two copies of each card.
  There are eight cards that has the same rank(club*2,diamond*2,heart*2,spade*2), so for every 8 cards, we make a new line. 
  In HoldEmDeck, we make a new line for every 4 cards.

5. Correct output:
[qinzhounick@shell lab_0]$ ./lab0
HoldEmDeck: 
2C 2D 2H 2S 
3C 3D 3H 3S 
4C 4D 4H 4S 
5C 5D 5H 5S 
6C 6D 6H 6S 
7C 7D 7H 7S 
8C 8D 8H 8S 
9C 9D 9H 9S 
10C 10D 10H 10S 
JC JD JH JS 
QC QD QH QS 
KC KD KH KS 
AC AD AH AS 

PinochleDeck: 
9C 9C 9D 9D 9H 9H 9S 9S 
JC JC JD JD JH JH JS JS 
QC QC QD QD QH QH QS QS 
KC KC KD KD KH KH KS KS 
10C 10C 10D 10D 10H 10H 10S 10S 
AC AC AD AD AH AH AS AS

