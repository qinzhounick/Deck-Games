#include "UnoColor.h"

using namespace std;

//shift operator<< for Uno color
std::ostream & operator<< (std::ostream& os, const Color& c) {
    //output all ranks
    if(c==Color::red){
        os <<  "red";
    }else if(c==Color::blue){
        os <<  "blue";
    }else if(c==Color::green){
        os <<  "green";
    }else if(c==Color::yellow){
        os <<  "yellow";
    }else if(c==Color::black){
        os <<  "black";
    }else if(c==Color::undefined){
        os <<  "?";
    }

    return os;
}



//prefix increment operator++ for Uno color
Color & operator++ (Color & c){
    //switch statement to move to the next rank
    switch(c) {
        case Color::red:
            c = Color::blue;
            break;
        case Color::blue:
            c = Color::green;
            break;
        case Color::green:
            c = Color::yellow;
            break;
        case Color::yellow:
            c = Color::black;
            break;
        case Color::black:
            c = Color::undefined;
            break;
        case Color::undefined:
            break;
    }

    return c;
}