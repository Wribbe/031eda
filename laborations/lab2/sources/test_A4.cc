#include <iostream>

#include "dictionary.h"
#include "test.h"

int main(void)
    /* Create and test expanded Dictionary class for ex A4. */
{
    print_test_header("A4: Extended Dictionary class");

    Dictionary four_dict({"this", "is", "a", "test"});
    test(four_dict.size() == 4, "Size should be 4.");

    print_test_results();
}
