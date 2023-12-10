1. Lab 3
Qinzhou(Nick) Song, Email: qinzhounick@wustl.edu
Xinyu(Jack) Li, Email: l.xinyujack@wustl.edu

once the player is removed, cannot be requested again!!!!!

2. Design Decisions:

(1)
To avoid the indexing conflicts, we made the program to ask the user to input the deck type for GoFish 
game, if no deck type is given, an error message will prompt and ask again.

3. Errors: 

(1) 
We wrote specializations for GoFishGame's constructor in the header file initially, which was causing
the problem that the compiler didn't know which one to use because there are multiple declarations. The 
TA told us that we only need one declaration of the general constructor in the header file, and in the
source file, we can make specializations. This fixed our issue.

(2)
We also had the problem of comparing string type value with the non-string type value. We tried to compare
input_rank from the command line to the card rank in players' hands, and it didn't work becasue they had 
different types, so we wrote two helper functions to convert string to "rank" type, and from "rank" type to
string.

(3)
We had the problem where the indexing of the players in "names"(containing players' names only) is wrong,
resulting in empty player's hand and books because there weren't any matches:

[qinzhounick@shell cse428_lab1]$ ./lab3 GoFish HoldEm
Invalid players! GoFish game takes 2-5 players. Please try again.
[qinzhounick@shell cse428_lab1]$ ./lab3 GoFish HoldEm A
Invalid players! GoFish game takes 2-5 players. Please try again.
[qinzhounick@shell cse428_lab1]$ ./lab3 GoFish HoldEm A B
Player A's hand is: 
Player A's books are: 
What card rank do you want to ask for?(card rank should be in your hand)

We used stoi() to convert the player names to integers as indexs so we can access the names, but index
starts from 0 and the result of stoi() starts with 1, so we subtracted 1 to solve the issue. We also changed
the prompt to ask the player to input the number of position of the player, for example, the first player is 1,
the third player is 3, to avoid input players have names other than just numbers, so we can use stoi() to get
the indexes.

(4)
When we tried to collect books, it was stuck in an infinite loop and the books will have one more similar rank 
every time:

Books: [9][9]
collecting books
Hands: 9C 9H 9H 9S JS QH QH 10C 10S 
Books: [9][9][9]
Hands: 9C 9H 9H 9S JS QH QH 10C 10S 
collecting books
Hands: 9C 9H 9H 9S JS QH QH 10C 10S

we found out that we were not passing reference of the deck to collect_books function so it was using the copy of
the deck every time it collects, so we fixed it and it by passing reference it will remove the card from the original
deck.

(5)
After we completed the game (all players' hands and the deck are empty), the game went in an infinite loop that kept
adding rounds:

End of turn: 
Player 1's books are: [2][4][5][6][7][8][10]

Player 2's hand is empty and the deck is empty. Turn skipped

End of turn: 
Player 2's books are: [3][9][J][Q][K][A]

Round 27042 finished:
Player 1 has 7 books made
Player 2 has 6 books made

This happened because we didn't update the Player Score map we created to track player's books. We added the sum of
books each deck can make at max so we could check if the total score of all players equals to the sum of the books 
the current deck could make, then end the game and print the result. We made sure after each collect_books is called, 
we update the score.

4. Output:
Our final output is as expected: 
    When request fails, player draw a card from the deck. If the deck is empty
        , the player is removed from the game and his hand goes back into the deck.
    When the player's hand is empty, they will draw a card from the deck. If the deck is empty
        , the player skips his turn.
    When the number of books reaches the max number of books and the deck is empty, the game ends
        , and the scores and the winner get printed.


Terminal output:

(1) when player is out of game:
Player 2's turn: 
Player 2's hand: 7H 10H JH QH KD AC 
Player 2's books: [2][4][5][6]
What card rank do you want to ask for?(card rank should be in your hand, letters must be capitalized.)
6
Which player do you want to ask for it from?(Index number of a player; Cannot be your Number)
E.g. If you want to request from the first player, input '1'; if third player, input '3'...
3
Invalid card rank. Please try again.
What card rank do you want to ask for?(card rank should be in your hand, letters must be capitalized.)
A
Which player do you want to ask for it from?(Index number of a player; Cannot be your Number)
E.g. If you want to request from the first player, input '1'; if third player, input '3'...
3
Go Fish!
Player 2 is removed from the game

(2) Some part of output leading to win:

Round 13 finished:
Player 1 has 2 books made
Player 2 has 4 books made
Player 3 has 1 books made

Player 1's turn: 
Player 1's hand: 10C 10D 10S JD JS QS KC KD KH AD AH AS 
Player 1's books: [8][9]
What card rank do you want to ask for?(card rank should be in your hand, letters must be capitalized.)
K
Which player do you want to ask for it from?(Index number of a player; Cannot be your Number)
E.g. If you want to request from the first player, input '1'; if third player, input '3'...
3
Request from player 3 succeeded! Got K from player 3

......(it's just player 1 getting all the cards he wants)

Player 1's turn: 
Player 1's hand: 10C 10D 10S 
Player 1's books: [8][9][J][Q][K][A]
What card rank do you want to ask for?(card rank should be in your hand, letters must be capitalized.)
10
Which player do you want to ask for it from?(Index number of a player; Cannot be your Number)
E.g. If you want to request from the first player, input '1'; if third player, input '3'...
3
Go Fish!
GoFish succeeded! Draw 10 from deck!

Player 1's hand is empty. Draw 7 from deck

Player 1's turn: 
Player 1's hand: 7H 
Player 1's books: [8][9][10][J][Q][K][A]
What card rank do you want to ask for?(card rank should be in your hand, letters must be capitalized.)
7
Which player do you want to ask for it from?(Index number of a player; Cannot be your Number)
E.g. If you want to request from the first player, input '1'; if third player, input '3'...
3
Request from player 3 succeeded! Got 7 from player 3

Player 1's turn: 
Player 1's hand: 7C 7H 
Player 1's books: [8][9][10][J][Q][K][A]
What card rank do you want to ask for?(card rank should be in your hand, letters must be capitalized.)
7
Which player do you want to ask for it from?(Index number of a player; Cannot be your Number)
E.g. If you want to request from the first player, input '1'; if third player, input '3'...
3
Request from player 3 succeeded! Got 7 from player 3

Player 1's turn: 
Player 1's hand: 7C 7D 7H 
Player 1's books: [8][9][10][J][Q][K][A]
What card rank do you want to ask for?(card rank should be in your hand, letters must be capitalized.)
7
Which player do you want to ask for it from?(Index number of a player; Cannot be your Number)
E.g. If you want to request from the first player, input '1'; if third player, input '3'...
3
Request from player 3 succeeded! Got 7 from player 3

Player 1's hand is empty and the deck is empty. Turn skipped

End of turn: 
Player 1's books are: [7][8][9][10][J][Q][K][A]

Player 3's hand is empty and the deck is empty. Turn skipped

End of turn: 
Player 3's books are: [3]

Round 14 finished:
Player 1 has 8 books made
Player 2 has 4 books made
Player 3 has 1 books made

Winners: Player 1 