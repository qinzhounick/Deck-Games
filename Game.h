#pragma once
#include <iostream>
#include <vector>
#include <string>

class Game {
    public:
        Game(int argc, const char * argv[]);
        virtual int play() = 0;
    protected:
        std::vector<std::string> names;
};