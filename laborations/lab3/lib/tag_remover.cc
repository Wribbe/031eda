#include "tag_remover.h"

/* Constructors. */
TagRemover::TagRemover(std::istream& cin)
    /* Take data from cin, convert to string and parse. */
{
    std::stringstream buffer;
    std::string line;
    while (std::getline(cin, line)) {
        buffer << line;
    }
    parse_string(buffer.str());
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
    std::regex newlines("\n");
    std::regex escaped_newlines("\\n");
    std::regex tags("<(.*?(\\n)*?)+>");
    std::regex trailing_whitspace("[:space:]*\n*$");
    std::regex empty_lines("^[:space:]*\n*$");

    /* Matching and replacing. */
    std::string current_string = input;
    current_string = std::regex_replace(current_string, newlines, "\\n");
    current_string = std::regex_replace(current_string, tags, "");
    current_string = std::regex_replace(current_string,
                                        escaped_newlines,
                                        "\n");
    current_string = std::regex_replace(current_string, empty_lines, "");
    current_string = std::regex_replace(current_string,
                                        trailing_whitspace,
                                        "");

    string_buffer << current_string;

    this->parse_results = string_buffer.str();
}
