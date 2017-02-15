#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <vector>
#include <unordered_set> // unordered_set.

#include "word.h"

class Dictionary {
public:
    /* Constructors. */
	Dictionary(const std::vector<std::string>& input_strings);
	Dictionary(const std::string& input_path = "output/proc-words.txt");
    /* Basic information. */
    bool is_empty();
    int size();
    int length();
    /* Utility functions. */
	bool contains(const std::string& word) const;
	std::vector<std::string> get_suggestions(const std::string& word) const;
private:
    /* Data. */
    std::unordered_set<std::string> internal_set;
    std::string input_path;
    static const size_t max_word_length = 25;
    std::vector<Word> words[max_word_length];
    int sort_matrix[max_word_length+1][max_word_length+1];
    /* Functions. */
    void strings_to_internal_set(std::vector<std::string> input_strings);
    void add_trigram_suggestions(std::vector<std::string>& suggestions,
                                 const std::string& word) const;
    void sort_candidates(std::vector<std::string> suggestions);
};

#endif
