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

void Dictionary::add_trigram_suggestions(std::vector<std::string>& suggestions,
                                         const std::string& word_string) const
    /* Only include stored words that have at least half the trigrams of the
     * supplied word. */
{
    std::vector<std::string> input_trigrams = make_ngrams(word_string, 3);
    size_t len_word = word_string.length();
    if (len_word > max_word_length) {
        return;
    }
    size_t min_len = len_word > 0 ? len_word-1 : len_word;
    size_t max_len = len_word < max_word_length ? len_word+1 : len_word;

    size_t num_trigrams = input_trigrams.size();
    size_t half_trigrams = num_trigrams/2; // ex. 7 -> 3, err on smaller side.

    /* Iterate over the interesting range. */
    for (size_t index = min_len; index <= max_len; ++index) {
        std::vector<Word> current_words = words[index];
        for (Word word : current_words) {
            std::vector<std::string> stored_trigrams = word.get_ngrams();
            unsigned int matches = match_trigrams(stored_trigrams, input_trigrams);
            if (matches >= half_trigrams) {
                suggestions.push_back(word.get_word());
            }
        }
    }
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
    std::vector<std::string> processed_lines;
    for (std::string input : input_strings) {
        std::vector<std::string> trigrams = make_ngrams(input, 3);
        std::string processed_string = make_output_string(input, trigrams);
        processed_lines.push_back(processed_string);
    }
    strings_to_internal_set(processed_lines);
}

// Non constructor functions:
void Dictionary::strings_to_internal_set(std::vector<std::string> input_strings)
    /* Take a vector of input strings and add them to the internal set. */
{
    std::string delimiters = " ";
    for (std::string current_line : input_strings) {
        std::vector<std::string> current_tokens;
        current_tokens = split_string(current_line, delimiters);
        const std::string word_string = std::string(current_tokens[0]);
        size_t len_word_string = word_string.length();
        if (len_word_string > max_word_length) {
            continue;
        }
        this->internal_set.insert(word_string);
        Word word = Word(word_string);
        this->words[len_word_string].push_back(word);
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
    add_trigram_suggestions(suggestions, word);
	return suggestions;
}

void Dictionary::rank_suggestions(std::string word,
                                  std::vector<std::string> suggestions)
    /* Sort candidates according to the following formula:
     *
     *  cost d(i,j) for changing i chars in p to the first j chars in other
     *  word q equals:
     *
     *      d(i,0) = i // first 'row/col' = 1,2,3 .. i.
     *      d(0,j) = i // first 'row/col' = 1,2,3 .. j.
     *      d(i,j) min( if p_i == q_j -> d(i-j,j-1) else d(i-1,j-1)+1,
     *                  d(i-1, j) + 1,
     *                  d(i, j-1) + 1.)
     *
     *  Use previous calculated values to step through then next 3 variables
     *  and see which one that results in the lowest cost. */
{
    // Set up initial matrix.
    for (size_t i = 0; i < max_word_length; ++i) {
        this->sort_matrix[0][i] = i;
        this->sort_matrix[i][0] = i;
    }
}
