#ifndef STRING_CAST_H
#define STRING_CAST_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <typeinfo>

void error(const std::string& input)
{
    throw std::invalid_argument("Could not convert: \"" + input + "\".");
}
template<typename T>
T general_parsing(const std::string& input)
    /* General parsing function used in all templates. */
{
    std::istringstream stream(input);
    T return_obj;
    stream >> return_obj;
    if ((stream.rdstate() & std::ifstream::failbit) != 0) {
        error(input);
    }
    return return_obj;
}

template<typename T>
T string_cast(const std::string& input)
    /* General string_cast implementation. */
{
    return general_parsing<T>(input);
}

template<>
int string_cast(const std::string& input)
    /* Specific string_cast implementation for int. */
{
    int object = general_parsing<int>(input);
    if (std::to_string(object).length() != input.length()) {
        error(input);
    }
    return object;
}

template<>
double string_cast(const std::string& input)
    /* Specific string_cast implementation for double. */
{
    double object = general_parsing<double>(input);
    std::string convertion = std::to_string(object);
    if (convertion.substr(0,input.length()).compare(input) != 0) {
        error(input);
    }
    return object;
}

#endif
