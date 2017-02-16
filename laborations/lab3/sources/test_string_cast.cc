#include "date.h"
#include "string_cast.h"

int main(void)
    /* Test program for string_cast. */
{
    std::string input = "2017-01-12";
    Date date;
    int i;
    double d;

    input = "5";
    i = string_cast<int>(input);
    std::cout << i << std::endl;

    input = "2017-01-12";
    date = string_cast<Date>(input);
    std::cout << date << std::endl;

    input = "same_string";
    std::string same_string = string_cast<std::string>(input);
    std::cout << same_string << std::endl;

    input = "5.92";
    d = string_cast<double>(input);
    std::cout << d << std::endl;

    try {
        input = "9!";
        i = string_cast<int>(input);
        std::cout << i << std::endl;
    } catch (std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    try {
        input = "5.92__10329487";
        d = string_cast<double>(input);
        std::cout << d << std::endl;
    } catch (std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}
