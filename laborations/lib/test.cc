#include "test.h"

size_t counter = 0;
size_t fails = 0;

std::stringstream check_bool(bool assertion)
    /* Break out counter. */
{
    std::stringstream buffer;
    counter += 1;
    if (assertion) {
        buffer << "[~]: ";
    } else {
        buffer << "[!]: ";
        fails += 1;
    }
    return buffer;
}

void test(bool assertion, std::string message)
    /* Wrapper around assert, with optional message. */
{
    std::stringstream buffer = check_bool(assertion);
    if(message.length()) {
        buffer << message;
    }
    buffer << std::endl;
    std::cerr << buffer.str();
}

void test(bool assertion, std::string correct, std::string result)
    /* A more pre-packaged variant of the test method. */
{
    std::stringstream buffer = check_bool(assertion);
    buffer << "Result: Should be " << correct << " was: " << result << ".";
    buffer << std::endl;
    std::cerr << buffer.str();
}

int print_test_results(void)
    /* Print result of tests. */
{
    std::cout << "--------" << std::endl;
    std::cout <<  "Result: " << fails << "/" << counter << \
        " assertions failed." << std::endl;
    return fails;
}

void print_test_header(std::string target)
    /* Print test header. */
{
    std::cout << "Running tests for: " << target << "." << std::endl;
    std::cout << "========" << std::endl;
}
