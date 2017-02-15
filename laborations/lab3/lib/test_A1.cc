#include <iostream>

#include "test.h"
#include "tag_remover.h"

int main(void)
{
    print_test_header("TagRemover");

    TagRemover no_change("Test");
    no_change.print(std::cout);

    print_test_results();
}
