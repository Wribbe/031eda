#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <vector>
#include <unordered_set> // unordered_set.

class Dictionary {
public:
	Dictionary(const std::vector<std::string>& input_strings);
	Dictionary(const std::string& input_path = "output/proc-words.txt");
	bool contains(const std::string& word) const;
	std::vector<std::string> get_suggestions(const std::string& word) const;
    bool is_empty();
    int size();
    int length();
private:
    std::unordered_set<std::string> internal_set;
    std::string input_path;
    void strings_to_internal_set(std::vector<std::string> input_strings);
};

#endif
