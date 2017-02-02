#include <iostream>
#include <fstream>
#include "coding.h"

int main(int argc, char * argv[])
{

  if (argc < 2) {
    std::cout << "[Usage:] ./encode <filename>." << std::endl;
    return EXIT_FAILURE;
  }

  // Get filename from argumtens.
  std::ifstream file(argv[1]);

  char c;
  while (file.get(c))
    std::cout << Coding().encode(c);
  file.close();
}
