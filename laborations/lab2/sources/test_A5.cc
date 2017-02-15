#include <iostream>

#include "dictionary.h"
#include "test.h"

int main(void)
    /* Create and test expanded Dictionary class for ex A4. */
{
    print_test_header("A5: Test rank_suggestions");

    std::string input = "tatal";

    Dictionary dict({input, "circus", "pivotal"});

    std::vector<std::string> suggestions;
    suggestions = dict.get_suggestions(input);
    test(suggestions[0].compare(input) == 0,
         "First suggestion should be equal to input.");

    print_test_results();
}
