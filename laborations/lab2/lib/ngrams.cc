#include "ngrams.h"
std::vector<std::string> make_ngrams(std::string string, size_t ngram_size)
    /* If the string is shorter or equal to ngram_size chars, return the
     * string. If the string is longer then ngram_size chars, return a sorted
     * vector of the n-grams. */
{
    std::vector<std::string> return_vector;
    if (string.length() <= ngram_size) {
        return_vector.push_back(string);
        return return_vector;
    }
    for (size_t index=ngram_size-1; index<string.length(); ++index) {
        return_vector.push_back(string.substr(index-(ngram_size-1), ngram_size));
    }
    // Sort the return vector.
    std::sort(return_vector.begin(), return_vector.end());
    // Return sorted vector.
    return return_vector;
}

