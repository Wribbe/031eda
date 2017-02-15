#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>      // stringstream.
#include <vector>
#include <utility>      // pair.

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
    suggestions = rank_suggestions(word, suggestions);
    suggestions = trim_suggestions(suggestions);
    return suggestions;
}

size_t Dictionary::get_smallest(std::vector<size_t> values) const
    /* Iterate through values and return the smallest one. */
{
    size_t min = values[0];
    for (size_t i=1; i<values.size(); ++i) {
        if (values[i] < min) {
            min = values[i];
        }
    }
    return min;
}

size_t Dictionary::edit_distance(const std::string& word,
                                 const std::string& suggestion) const
    /* Calculate and return the edit distance required to transform the word
     * into the suggestion according to the following formula:
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
    // Set matrix.
    size_t sort_matrix[max_word_length+1][max_word_length+1] = {0};
    for (size_t i = 0; i < max_word_length; ++i) {
        sort_matrix[i][0] = i;
        sort_matrix[0][i] = i;
    }

    // Get maximal ranges.
    size_t max_i = word.size();
    size_t max_j = suggestion.size();

    // Iterate over the matrix and calculate distances.
    for (size_t i = 1; i<=max_i; ++i) {
        char c_word = word[i-1];
        for (size_t j = 1; j<=max_j; ++j) {
            char c_suggestion = suggestion[j-1];
            size_t prev_diag = sort_matrix[i-1][j-1];
            // Calculate value based on equality and diag.
            size_t val_eq = c_word == c_suggestion ? prev_diag : prev_diag+1;
            // Calculate values based on previous i and j.
            size_t val_prev_i = sort_matrix[i-1][j]+1;
            size_t val_prev_j = sort_matrix[i][j-1]+1;
            // Set the current value to the smallest value of the three.
            sort_matrix[i][j] = get_smallest({val_eq, val_prev_i, val_prev_j});
        }
    }

    return sort_matrix[max_i][max_j];
}

std::vector<std::string>
Dictionary::rank_suggestions(const std::string& word,
                             const std::vector<std::string>& suggestions) const
    /* Rank and return suggestions based on edit distance. */
{
    std::vector<std::pair<size_t, std::string>> sorting_vector;

    for (const std::string& suggestion : suggestions) {
        size_t distance = edit_distance(word, suggestion);
        sorting_vector.push_back(std::make_pair(distance, suggestion));
    }

    // Sort sorting_vector.
    std::sort(sorting_vector.begin(), sorting_vector.end());

    // Go through and pull out all words.
    std::vector<std::string> return_vector;
    for (std::pair<size_t, std::string> pair : sorting_vector) {
        return_vector.push_back(pair.second);
    }

    return return_vector;
}

std::vector<std::string>
Dictionary::trim_suggestions(const std::vector<std::string>& suggestions) const
    /* Return the 5 first suggestions. */
{
    if (suggestions.size() == 0) {
        return std::vector<std::string>();
    }
    size_t return_num = 5;
    return std::vector<std::string>(suggestions.begin(),
                                    suggestions.begin()+return_num);
}
