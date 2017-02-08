#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "word.h"
#include "ngrams.h"


Word::Word(const std::string& w) :
    word(w),
    ngrams(make_ngrams(w, 3))
    /* Word constructor. */
{
    /* Empty. */
}


std::string Word::get_word() const
    /* Return the word. */
{
	return this->word;
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


unsigned int Word::get_matches(const std::string& string) const
    /* Returns how many trigrams from the string that exist in the stored
     * trigram vector. Both vectors are alphabetically sorted. */
{
    unsigned int matches = 0;

    std::vector<std::string> stored_trigrams = this->ngrams;
    std::vector<std::string> input_trigrams = make_ngrams(string, 3);

    auto iter_stored = stored_trigrams.begin();
    auto iter_input = input_trigrams.begin();

    auto iter_stored_end = stored_trigrams.end();
    auto iter_input_end = input_trigrams.end();

    bool at_end_stored = iter_stored == iter_stored_end;
    bool at_end_input = iter_input == iter_input_end;

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
