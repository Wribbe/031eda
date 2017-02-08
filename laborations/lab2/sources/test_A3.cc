#include <iostream>
#include <sstream>      // Stringstream.

#include <assert.h>

#include "word.h"
#include "test.h"

int main(void)
    /* Create and test the Word class. */
{
    std::string input_word = "aaa";

    Word word(input_word);

    test(word.get_word().compare(input_word) == 0,
        "The returned word should be correct.");
    test(word.get_word().compare("Not the input word") != 0,
        "The returned word should not be correct.");

    test(word.get_matches("aaa") == 1,
        "Returned number of trigrams should be 1.");

    test(word.get_matches("bbb") == 0,
        "Returned number of trigrams should be 0.");

    test(word.get_matches("aabbbaaa") == 1,
        "Returned number of trigrams for longer string should be 1.");

    print_test_results();
}
