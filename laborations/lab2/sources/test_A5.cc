#include <iostream>

#include "dictionary.h"
#include "test.h"

int main(void)
    /* Create and test expanded Dictionary class for ex A4. */
{
    print_test_header("A5: Test rank_suggestions");

    std::string correct = "clown";
    std::string error = "clownd";

    Dictionary dict;

    std::vector<std::string> suggestions;
    suggestions = dict.get_suggestions(error);
    test(suggestions[0].compare(correct) == 0,
         "First suggestion should be equal to <correct>.");

    std::cout << "Returned suggestions:" << std::endl;
    for (std::string suggestion : suggestions) {
        std::cout << "  " << suggestion << std::endl;
    }

    test(suggestions.size() == 5, "Should return 5 suggestions.");

    print_test_results();
}
