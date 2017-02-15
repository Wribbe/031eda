#ifndef NGRAMS_H
#define NGRAMS_H

#include <algorithm>
#include <string>
#include <vector>

/* Return the supplied string as n-grams. */
std::vector<std::string> make_ngrams(const std::string& string, size_t ngram_size);
/* Take string and ngrams and output a processed string. */
std::string make_output_string(const std::string word,
                               const std::vector<std::string> ngrams);
/* Return the number of trigrams from the input that are in the stored
 * trigrams. */
unsigned int match_trigrams(const std::vector<std::string>& stored_trigrams,
                            const std::vector<std::string>& input_trigrams);

#endif
