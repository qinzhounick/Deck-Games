//File Name: Game.h
//Authors: Qinzhou(Nick) Song, Xinyu(Jack) Li
//Email: qinzhounick@wustl.edu, l.xinyujack@wustl.edu
//Summary: header file for Game
//  declare base Game class 

#pragma once
#include <iostream>
#include <vector>
#include <string>

//Game class
class Game {
    public:
        Game(int argc, const char * argv[]); //Game class constructor
        virtual int play() = 0; //pure virtual play function
    protected:
        std::vector<std::string> names; //protected vector to store names
};