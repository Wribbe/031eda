#include "to_string.h"
#include "date.h"
#include "test.h"

int main(void)
{
    print_test_header("toString()");

    double d = 1.234;
    std::string correct_date = "2017-02-16";
    std::string correct_double = "1.234";
    Date date(2017, 2, 16);

    std::string double_conv = toString(d);
    std::string date_conv = toString(date);

    test(correct_date.compare(date_conv) == 0,
         correct_date,
         date_conv);
    test(correct_double.compare(double_conv) == 0,
         correct_double,
         double_conv);

    print_test_results();
}
