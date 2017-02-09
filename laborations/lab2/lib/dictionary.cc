#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>      // stringstream.
#include <vector>

#include "word.h"
#include "dictionary.h"
#include "ngrams.h"

// Local functions.
// ----------------

std::vector<std::string> split_string(std::string string, std::string delims)
    /* Split string on any occurrence of a character described by the string
     * delims. Return a vector of split tokens. */
{
    std::stringstream buffer;
    std::string temp_string = "";
    std::vector<std::string> tokens;
    for (char c : string) {
        if (delims.find(c) != std::string::npos) { // c is a delimiter.
            temp_string = buffer.str();
            std::stringstream().swap(buffer);
            if(!temp_string.empty()) {
                tokens.push_back(temp_string);
            }
        } else { // not delimiter, push to buffer.
            buffer << c;
        }
    }
    // Check if there is anything left in buffer, ex, no delimiter at all.
    temp_string = buffer.str();
    if (!temp_string.empty()) {
        tokens.push_back(temp_string);
    }
    return tokens;
}

std::vector<std::string> path_to_lines(const std::string& input_path)
    /* Take a input path and return a vector that has each line as an
     * element.  */
{
    // Open input file.
    std::ifstream file_handle(input_path);
    std::vector<std::string> return_vector;
    if (file_handle.is_open()) {
        std::string current_line = "";
        while(std::getline(file_handle, current_line)) {
            return_vector.push_back(current_line);
        }
        // Close input file.
        file_handle.close();
    }
    return return_vector;
}

// Class functions.
// ----------------

// Constructors:
Dictionary::Dictionary(const std::string& input_path) :
    internal_set(std::unordered_set<std::string>()),
    input_path(input_path)
    /* Take path, convert to lines, add to inner set. */
{
    std::vector<std::string> input_strings = path_to_lines(input_path);
    strings_to_internal_set(input_strings);
}


Dictionary::Dictionary(const std::vector<std::string>& input_strings) :
    internal_set(std::unordered_set<std::string>()),
    input_path("")
    /* Iterate over supplied lines and append to internal set. */
{
    strings_to_internal_set(input_strings);
}

// Non constructor functions:
void Dictionary::strings_to_internal_set(std::vector<std::string> input_strings)
    /* Take a vector of input strings and add them to the internal set. */
{
    std::string delimiters = " ";
    for (std::string current_line : input_strings) {
        std::vector<std::string> current_tokens;
        current_tokens = split_string(current_line, delimiters);
        std::string word = current_tokens[0];
        this->internal_set.insert(word);
    }
}


bool Dictionary::contains(const std::string& word) const
    /* Return boolean reflecting if word is present in dictionary or not. */
{
    return internal_set.find(word) != internal_set.end();
}

int Dictionary::size()
    /* Return size/length of Dictionary. */
{
    return internal_set.size();
}

int Dictionary::length()
    /* Return size/length of Dictionary. */
{
    return size();
}


bool Dictionary::is_empty()
    /* Return boolean reflecting if the dictionary is empty or not. */
{
    return this->size() == 0;
}

std::vector<std::string> Dictionary::get_suggestions(const std::string& word) const {
    std::vector<std::string> suggestions;
	return suggestions;
}
