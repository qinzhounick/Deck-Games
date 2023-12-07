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