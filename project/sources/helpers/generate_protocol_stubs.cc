#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

struct Line
    /* Wrapper class for a string to make it possible to read a file
     * line-by-line through the istream iterators. */
{
    std::string data;
    operator std::string() const {
        return data;
    }
    size_t find(const std::string& str, size_t pos=0) const {
        (void)pos;
        size_t found = data.find(str);
        if (found!=std::string::npos) {
            return found;
        }
        return 0;
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
    string.erase(end, string.length());
}

void printer(Line line)
{
    std::string token = "=";
    if (line.find(token)) {
        std::string string = line.data;
        split(string, token);
        strip(string);
        std::transform(string.begin(), string.end(),string.begin(),::tolower);
        std::cout << "void f" << string << std::endl;
        std::cout << "{" << std::endl;
        std::cout << "}" << std::endl;
    }
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
