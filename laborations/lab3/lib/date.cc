#include <ctime>  // time and localtime
#include "date.h"

int Date::daysPerMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

/* Constructors. */
Date::Date(void)
    /* No input constructor. */
{
	time_t timer = time(0); // time in seconds since 1970-01-01
	tm* locTime = localtime(&timer); // broken-down time
	year = 1900 + locTime->tm_year;
	month = 1 + locTime->tm_mon;
	day = locTime->tm_mday;
}


Date::Date(int y, int m, int d) :
    year(y),
    month(m),
    day(d)
    /* Specified Date constructor. */
{
}


std::istream& operator>>(std::istream& cin, Date& obj)
    /* Overload operator>> with istream to make it possible to pipe input from
     * cin to a date object. Set failbit if format was wrong. */
{
    std::string input;
    std::getline(cin, input);
    bool correct = obj.format_input(input);
    if (!correct) {
        cin.setstate(std::ios::failbit);
    }
    return cin;
}


void operator>>(std::string& input, Date& obj)
    /* Overload operator>> for string input. */
{
    obj.format_input(input);
}


std::ostream& operator<<(std::ostream& cout, const Date& obj)
    /* Overload operator<< so that Date objects can be passed to output
     * streams. */
{
    cout << std::setw(4) << std::setfill('0') << obj.getYear() << '-';
    cout << std::setw(2) << std::setfill('0') << obj.getMonth() << '-';
    cout << std::setw(2) << std::setfill('0') << obj.getDay();

    return cout;
}


bool Date::format_input(std::string& input)
    /* Process input, return true or false signaling if the format was correct
     * or not. */
{
    std::regex re_year("^\\d{4}");
    std::regex re_month("-\\d{2}-");
    std::regex re_day("-\\d{2}$");

    std::regex dashes("-");

    std::smatch string_match;
    int counter = 0;
    int tokens[3] = {0};
    for(std::regex regex : {re_year, re_month, re_day}) {
        std::regex_search(input, string_match, regex);
        if (string_match.size() != 1) {
            return false;
        }
        std::string match = string_match[0];
        std::string stripped_match = std::regex_replace(match, dashes, "");
        tokens[counter] = std::stoi(stripped_match);
        if (tokens[counter] <= 0) {
            return false;
        }
        counter++;
    }

    enum token_index { YEAR, MONTH, DAY };

    if (tokens[MONTH] > num_months) {
        return false;
    }
    if (tokens[DAY] > daysPerMonth[tokens[MONTH]]) {
        return false;
    }

    year = tokens[YEAR];
    month = tokens[MONTH];
    day = tokens[DAY];

    return true;
}


int Date::getYear() const
{
	return year;
}

int Date::getMonth() const
{
	return month;
}

int Date::getDay() const
{
	return day;
}

void Date::next()
    /* Step through to the next date. */
{
    day++;
    if (day > daysPerMonth[month]) {
        day = 1;
        month++;
    }
    if (month > num_months) {
        month = 1;
        year++;
    }
}
