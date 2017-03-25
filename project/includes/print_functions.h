#ifndef PRINT_FUNCTION_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>

size_t find(const std::string& str, const std::string& source);
void split(std::string& string, std::string& token);
void strip(std::string& string);

template <typename T>
void print(const T& string)
    /* Print string to std::cout without newline. */
{
    std::cout << string;
}

template <typename T>
void println(const T& string)
    /* Print string to std::cout with newline. */
{
    print(string);
    std::cout << std::endl;
}

void add_includes(std::vector<std::string> libs);

std::vector<std::string> get_lines(std::string filepath);
#endif
