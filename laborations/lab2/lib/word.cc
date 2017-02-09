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


const std::string& Word::get_word() const
    /* Return the word. */
{
	return this->word;
}


std::vector<std::string>& Word::get_ngrams(void)
    /* Return reference to internal ngrams. */
{
    return ngrams;
}

unsigned int Word::get_matches(const std::string& string) const
{
    std::vector<std::string> stored_trigrams = this->ngrams;
    std::vector<std::string> input_trigrams = make_ngrams(string, 3);

    return match_trigrams(stored_trigrams, input_trigrams);
}
