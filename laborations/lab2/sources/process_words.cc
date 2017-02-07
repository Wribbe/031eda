#include <fstream>
#include <iostream>
#include <istream>
#include <string>

int main(int argc, char * argv[])
    /* Process a input file at a given path by the command line arguments.
     * The input file contains one word per line, and the output should contain
     * the same word together with a number of how many trigrams the word can
     * be split into, followed by the list of the sorted trigrams. */
{
    if (argc < 2) {
        std::cerr << "[Usage]: " << argv[0] << " <input file>" << std::endl;
        return EXIT_FAILURE;
    }

    // Try to open the supplied file.
    std::ifstream input_file(argv[1]);

    if (!input_file.is_open()) {
        std::cerr << "[!]: Could not open <" << argv[1] << ">, no such file, " << \
            "aborting." << std::endl;
        return EXIT_FAILURE;
    }

    // Process and print all the lines in the file.
    std::string line = "";
    while (std::getline(input_file, line)) {
        std::cout << line << std::endl;
    }
}
