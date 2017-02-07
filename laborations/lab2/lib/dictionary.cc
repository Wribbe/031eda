#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>      // stringstream.
#include <vector>

#include "word.h"
#include "dictionary.h"

using namespace std;

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

Dictionary::Dictionary(const std::string& input_path) :
    internal_set(std::unordered_set<std::string>()),
    input_path(input_path)
    /* Dictionary constructor. */
{
    // Open input file.
    std::ifstream file_handle(input_path);
    std::string delimiters = " ";
    if (file_handle.is_open()) {
        std::string current_line = "";
        while(std::getline(file_handle, current_line)) {
            std::vector<std::string> current_tokens;
            current_tokens = split_string(current_line, delimiters);
            std::string word = current_tokens[0];
            std::cout << word << std::endl;
        }
    }
    // Close input file.
    file_handle.close();
}

bool Dictionary::contains(const string& word) const
    /* Return boolean reflecting if word is present in dictionary or not. */
{
    return internal_set.find(word) != internal_set.end();
}

int Dictionary::size()
    /* Return size of Dictionary. */
{
    return internal_set.size();
}


bool Dictionary::is_empty()
    /* Return boolean reflecting if the dictionary is empty or not. */
{
    return this->size() == 0;
}

vector<string> Dictionary::get_suggestions(const string& word) const {
	vector<string> suggestions;
	return suggestions;
}
