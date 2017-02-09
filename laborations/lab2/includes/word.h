#ifndef WORD_H
#define WORD_H

#include <string>
#include <vector>

class Word {
public:
    /* Creates a word w with the sorted trigrams t */
    Word(const std::string& w);

    /* Returns the word */
    const std::string& get_word() const;

    /* Returns how many of the trigrams in t that are present
     in this word's trigram vector */
    unsigned int get_matches(const std::string& t) const;
    std::vector<std::string>& get_ngrams();
private:
    std::string word;
    std::vector<std::string> ngrams;
};

#endif
