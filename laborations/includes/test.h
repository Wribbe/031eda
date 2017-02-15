#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <sstream>

#include "assert.h"

void test(bool assertion, std::string message = "");
int print_test_results(void);
void print_test_header(std::string target);

#endif
