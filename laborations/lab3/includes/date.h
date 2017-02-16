#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <regex>
#include <string>

class Date {
public:
    /* Constructors. */
	Date();                    // today's date
	Date(int y, int m, int d); // yyyy-mm-dd
    /* Public functions. */
	int getYear() const;       // get the year
	int getMonth() const;      // get the month
	int getDay() const;        // get the day
	void next();               // advance to next day
    /* Frindes. */
    friend std::istream& operator>>(std::istream& cin, Date& obj);
    friend void operator>>(std::string& input, Date& obj);
private:
    /* Private data. */
	int year;  // the year (four digits)
	int month; // the month (1-12)
	int day;   // the day (1-..)
    static const int num_months = 12;
	static int daysPerMonth[num_months]; // number of days in each month
    /* Private functions. */
    bool format_input(std::string& input);
};

/* Non-member operator-overloading. */
std::istream& operator>>(std::istream& cin, Date& obj);
void operator>>(std::string& input, Date& obj);

#endif
