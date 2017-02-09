#include <sstream>

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

std::string make_output_string(std::string word,
                               std::vector<std::string> ngrams)
    /* Take a word and its n-gram vector and return a string that matches the
     * desired output format. */
{
    std::stringstream buffer;
    buffer << word << " ";
    size_t num_ngrams = ngrams.size();
    buffer << num_ngrams << " ";
    for (size_t i = 0; i<num_ngrams; ++i) {
        buffer << ngrams[i];
        // Don't append after last ngram.
        if (i < num_ngrams-1) {
            buffer << " ";
        }
    }
    return buffer.str();
}


bool advance(std::vector<std::string>::iterator& iterator,
             std::vector<std::string>::iterator& end)
    /* Advance the iterator. If the iterator is at its end point, don't
     * advance. Return boolean value reflecting if the iterator has reached its
     * endpoint or not. */
{
    if (iterator != end) {
        iterator++;
    }
    return iterator == end;
}


unsigned int match_trigrams(std::vector<std::string> stored_trigrams,
                            std::vector<std::string> input_trigrams)
    /* Returns how many trigrams from the input that exist in the stored
     * trigram vector. Both vectors are alphabetically sorted. */
{
    auto iter_stored = stored_trigrams.begin();
    auto iter_input = input_trigrams.begin();

    auto iter_stored_end = stored_trigrams.end();
    auto iter_input_end = input_trigrams.end();

    bool at_end_stored = iter_stored == iter_stored_end;
    bool at_end_input = iter_input == iter_input_end;

    unsigned int matches = 0;

    while (!at_end_stored && !at_end_input) {

        // Use the fact that the vectors are sorted.

        // If the current trigram in the input vector starts with a character
        // that is 'larger' then the current trigram in the stored trigram, the
        // stored iterator can be advanced until it matches or is larger then
        // the current input trigram.

        // If the stored trigram hits the end of the internal trigram list and
        // the inputs first character is still larger, break the loop, no more
        // matches.

        int comparison = (*iter_input).compare(*iter_stored);
        //  0: Equal.
        // <0: The first non-matching char of iter_stored is lower then the
        //     char in the iter_input string.
        // >0: The first non-matching char of iter_stored is greater then the
        //     char in the  iter_input string.
        if (comparison == 0) {
            matches++;
            at_end_stored = advance(iter_stored, iter_stored_end);
            at_end_input = advance(iter_input, iter_input_end);
        } else if (comparison < 0) {
            at_end_input = advance(iter_input, iter_input_end);
        } else {
            at_end_stored = advance(iter_stored, iter_stored_end);
        }
    }

    return matches;
}
