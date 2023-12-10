//File Name: UnoColor.h
//Authors: Qinzhou(Nick) Song, Xinyu(Jack) Li
//Email: qinzhounick@wustl.edu, l.xinyujack@wustl.edu
//Summary: Header file for UnoColor
//  declare the enum class for Color and the overwrite the shift operator and increment operator

#pragma once
#include <ostream>

enum class Color {
    red,
    blue,
    green,
    yellow,
    black,
    undefined
};

std::ostream & operator<< (std::ostream& os, const Color& c);
Color & operator++ (Color& c);