#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <sstream>

#include "assert.h"

void test(bool assertion, std::string message = "");
void print_test_results(void);

#endif
