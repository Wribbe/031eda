#include <iostream>

#include "dictionary.h"
#include "test.h"

int main(void)
    /* Create and test expanded Dictionary class for ex A4. */
{
    print_test_header("A4: Extended Dictionary class");

    Dictionary four_dict({"this", "is", "a", "test"});
    test(four_dict.size() == 4, "Size should be 4.");

    Dictionary one_non_26({"aaaaaaaaaaaaaaaaaaaaaaaaaaa", // > 25
                           "bbbbbbbbbbbbbbbbbbbbbbbbbbb", // > 25
                           "a"}); // < 25
    test(one_non_26.size() == 1, "Size of one_non_26 should be 1.");

    Dictionary three_sugg({"tthisisalongword",
                           "cccccccccccc",
                           "thisisalongwor",
                           "thi",
                           "thisisalongwordc"});

    unsigned int num_suggestions;
    num_suggestions = three_sugg.get_suggestions("thisisalongword").size();
    test(num_suggestions == 3, "Should return 3 suggestions.");

    print_test_results();
}
