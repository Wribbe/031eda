#include "to_string.h"

template<typename T>
std::string toString(T& input)
    /* Put input into buffer, return buffer as a string. */
{
    std::stringstream buffer;
    buffer << input;
    return buffer.str();
}
