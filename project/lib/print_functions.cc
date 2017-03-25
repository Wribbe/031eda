#include "print_functions.h"

struct Line
    /* Wrapper class for a string to make it possible to read a file
     * line-by-line through the istream iterators. */
{
    std::string data;
    operator std::string() const {
        return data;
    }
};

size_t find(const std::string& str, const std::string& source)
{
    size_t found = source.find(str);
    if (found!=std::string::npos) {
        return found;
    }
    return 0;
}

std::istream& operator>>(std::istream &stream, Line &line)
    /* Operation that deposit's the input into the line data string. */
{
    std::getline(stream, line.data);
    return stream;
}


std::ostream& operator<<(std::ostream &stream, Line &line)
    /* Operation that takes data from line and supplies it to the stream. */
{
    stream << line.data;
    return stream;
}


void split(std::string& string, std::string& token)
    /* Split string at token and return left item. */
{
    auto end = string.find(token);
    string.erase(end, string.length());
}

void strip(std::string& string)
    /* Strip whitespace from front and back of string. */
{
    std::string whitespace = " \t";
    auto start = string.find_first_not_of(whitespace);
    auto end = string.find_last_not_of(whitespace);
    string.erase(0, start);
    string.erase(end-1, string.length());
}

void add_includes(std::vector<std::string> libs)
    /* Print libraries that should be included. */
{
    for (std::string lib : libs) {
        println("#include " + lib);
    }
    println("");
}

std::vector<std::string> get_lines(std::string filepath)
    /* Open file and return vector with the lines from the given file path. */
{
    std::ifstream file(filepath);
    if(!file.is_open()) {
        std::cerr << "No such file: " << filepath << ", aborting." << std::endl;
        exit(EXIT_FAILURE);
    }
    std::vector<std::string> lines;
    auto iter = std::istream_iterator<Line>(file);
    auto end = std::istream_iterator<Line>();
    std::copy(iter, end, back_inserter(lines));
    return lines;
}
