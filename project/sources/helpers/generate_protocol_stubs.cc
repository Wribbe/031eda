#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>

struct Line
    /* Wrapper class for a string to make it possible to read a file
     * line-by-line through the istream iterators. */
{
    std::string data;
    operator std::string() const {
        return data;
    }
};


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

void printer(Line line)
{
    std::cout << line << std::endl;
}


int main(int argc, char ** argv)
{
    if (argc < 2) {
        std::string exec_path = std::string(argv[0]);
        std::string exec_name = exec_path.substr(exec_path.find_last_of('/')+1);
        std::cerr << "Usage: ./" << exec_name << " protocol.h" << std::endl;
        return EXIT_FAILURE;
    }

    std::string filepath(argv[1]);

    std::ifstream file(filepath);
    if(!file.is_open()) {
        std::cerr << "No such file: " << filepath << ", aborting." << std::endl;
        return EXIT_FAILURE;
    }

    std::istream_iterator<Line> iter = std::istream_iterator<Line>(file);
    std::istream_iterator<Line> end;
    for_each(iter, end, printer);
}
