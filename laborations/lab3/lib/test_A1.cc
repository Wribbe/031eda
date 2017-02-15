#include <iostream>

#include "test.h"
#include "tag_remover.h"

int main(void)
{
    print_test_header("TagRemover");

    std::stringstream result_buffer;
    std::string result;

    std::string input = "Test";

    TagRemover no_change(input);
    no_change.print(result_buffer);
    result = result_buffer.str();
    std::stringstream().swap(result_buffer);
    test(input.compare(result) == 0,
         "Input: " + input + " should be unchanged, was: "+ result);

    TagRemover still_test("<TestTag>"+input+"</TestTag>");
    still_test.print(result_buffer);
    result = result_buffer.str();
    std::stringstream().swap(result_buffer);
    test(input.compare(result) == 0,
         "Input: " + input + " should be unchanged, was: " + result);

    TagRemover newline_test("<TestTag>"+input+"</TestTag\non new line>");
    newline_test.print(result_buffer);
    result = result_buffer.str();
    std::stringstream().swap(result_buffer);
    test(input.compare(result) == 0,
         "Input: " + input + " should be unchanged, was: " + result);


    print_test_results();
}
