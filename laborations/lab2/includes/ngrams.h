#ifndef NGRAMS_H
#define NGRAMS_H

#include <algorithm>
#include <string>
#include <vector>

/* Return the supplied string as n-grams. */
std::vector<std::string> make_ngrams(std::string string, size_t ngram_size);

#endif
