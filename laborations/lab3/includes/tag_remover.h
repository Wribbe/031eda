#ifndef TAG_REMOVER_H
#define TAG_REMOVER_H

#include <iostream>
#include <regex>
#include <sstream>
#include <string>

class TagRemover {
public:
    /* Constructors. */
    TagRemover(std::istream& cin);
    TagRemover(const std::string& input);
    /* Public functions. */
    void print(std::ostream& cout);
private:
    /* Data. */
    std::string parse_results;
    /* Functions. */
    void parse_string(const std::string& input);
};

#endif
