#include <algorithm>    // reverse.
#include <fstream>      // ifstream/ofstream.
#include <iostream>     // cin/cout/cerr.
#include <istream>      //
#include <string>       // string.
#include <vector>       // vector.

std::vector<std::string> make_ngrams(std::string string, size_t ngram_size)
    /* If the string is shorter or equal to ngram_size chars, return the
     * string. If the string is longer then ngram_size chars, return a sorted
     * vector of the n-grams. */
{
    std::vector<std::string> return_vector;
    if (string.length() <= ngram_size) {
        return_vector.push_back(string);
        return return_vector;
    }
    for (size_t index=ngram_size-1; index<string.length(); ++index) {
        return_vector.push_back(string.substr(index-(ngram_size-1), ngram_size));
    }
    // Sort the return vector.
    std::sort(return_vector.begin(), return_vector.end());
    // Return sorted vector.
    return return_vector;
}


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
        for (std::string string : make_ngrams(line, 3)) {
            std::cout << string << " ";
        }
        std::cout << std::endl;
    }
}
