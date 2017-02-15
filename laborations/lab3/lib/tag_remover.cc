#include "tag_remover.h"

/* Constructors. */
TagRemover::TagRemover(std::istream& cin)
    /* Take data from cin, convert to string and parse. */
{
}

TagRemover::TagRemover(const std::string& input)
    /* Take input string and parse. */
{
    parse_string(input);
}

/* Public functions. */

void TagRemover::print(std::ostream& cout)
    /* Print output to ostream. */
{
    cout << this->parse_results;
}

/* Private functions. */

void TagRemover::parse_string(const std::string& input)
    /* Take a input string parse it and return parsed string. */
{
    std::stringstream string_buffer;

    /* Regular expressions. */
    std::regex match_tags("<.*?>");

    /* Matching and replacing. */
    string_buffer << std::regex_replace(input, match_tags, "");

    this->parse_results = string_buffer.str();
}
