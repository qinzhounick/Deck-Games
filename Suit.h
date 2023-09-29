//File Name: Suit.h
//Authors: Qinzhou(Nick) Song, Xinyu(Jack) Li
//Email: qinzhounick@wustl.edu, l.xinyujack@wustl.edu
//Summary: header file for Suit
//  declare enum Suit and two overloaded operators

#pragma once
#include <ostream>
#include <iostream>
#include <vector>
#include <string>


//declare all the suits
enum Suit {clubs = 0, diamonds = 1, hearts = 2, spades = 3, undefined = 4};

//return 0 for success
const int SUCCESS = 0;

//overloaded operators
std::ostream & operator<< (std::ostream& os, const Suit& s);
Suit & operator++ (Suit& s);