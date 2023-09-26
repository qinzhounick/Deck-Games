#pragma once
#include <ostream>
#include <iostream>

using namespace std;

enum Suit {
    clubs = 0,
    diamonds = 1,
    hearts = 2,
    spades = 3,
    undefined = 4
};


enum error {
    SUCCESS = 0
};

ostream & operator<< (ostream& os, const Suit& s);

Suit & operator++ (Suit& s);