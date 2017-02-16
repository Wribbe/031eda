#include <fstream>
#include <iostream>

#include "test.h"
#include "tag_remover.h"

int main(void)
{
    print_test_header("TagRemover");
    std::string compare;

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

    std::ifstream file("input/test_A1_input.txt");
    TagRemover file_data_test(file);
    file_data_test.print(result_buffer);
    result = result_buffer.str();
    std::stringstream().swap(result_buffer);
    compare = "Test Test\n";
    test(compare.compare(result) == 0,
         "Result: "+result+" should be: "+compare+" was: "+result);

    TagRemover specials_test("&lt;&gt;&nbsp;&amp;");
    compare = "<> &";
    specials_test.print(result_buffer);
    result = result_buffer.str();
    std::stringstream().swap(result_buffer);
    test(compare.compare(result) == 0,
         "Result: "+result+" should be: "+compare+" was: "+result);

    std::ifstream html_file("input/test.html");
    TagRemover html_test(html_file);
    html_test.print(std::cout);

    print_test_results();
}
