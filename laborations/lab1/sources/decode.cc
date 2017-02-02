#include <iostream>
#include <fstream>
#include <string>
#include "coding.h"

int main(int argc, char * argv[])
{

  std::string executable_name = "decode";

  if (argc < 2) {
    std::cout << "[Usage:] ./";
    std::cout << executable_name;
    std::cout << " <filename>." << std::endl;
    return EXIT_FAILURE;
  }

  std::string input_extension = ".enc";
  std::string output_extension = ".dec";

  std::string output_directory = "output";
  std::string input_directory = "input";

  // Get filename from argumtens.
  std::ifstream file(argv[1]);

  // Create output filename.
  std::string output_filename(argv[1]);
  auto s_end = output_filename.end();
  output_filename.replace(s_end-sizeof(".***"), s_end, ".enc");
  std::cout << output_filename << std::endl;

  char c;
  while (file.get(c))
    std::cout << Coding().decode(c);
  file.close();
}
