#ifndef TO_STRING_H
#define TO_STRING_H

#include <iostream>
#include <sstream>
#include <string>

template<typename T>
std::string toString(const T& input)
{
    std::stringstream buffer;
    buffer << input;
    return buffer.str();
}

#endif
