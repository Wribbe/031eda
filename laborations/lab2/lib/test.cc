#include "test.h"

size_t counter = 0;
size_t fails = 0;

void test(bool assertion, std::string message)
    /* Wrapper around assert, with optional message. */
{
    std::stringstream buffer;
    counter += 1;
    if (assertion) {
        buffer << "[~]: ";
    } else {
        buffer << "[!]: ";
        fails += 1;
    }
    if(message.length()) {
        buffer << message;
    }
    buffer << std::endl;
    std::cerr << buffer.str();
}

void print_test_results(void)
    /* Print result of tests. */
{
    std::cout << "--------" << std::endl;
    std::cout <<  "Result: " << fails << "/" << counter << \
        " assertions failed." << std::endl;
}
