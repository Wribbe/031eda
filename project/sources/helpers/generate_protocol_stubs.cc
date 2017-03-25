#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>

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
    string.erase(end-1, string.length());
}

//std::map<std::string,void (*) (void)> map_functions;
std::map<std::string,std::string> string_map;

void printer(Line line)
{
    std::string token = "=";
    if (line.find(token)) {
        std::string string = line.data;
        split(string, token);
        strip(string);
        std::string lower(string);
        std::transform(string.begin(), string.end(),lower.begin(),::tolower);
        std::string function_name = "f_" + lower;
        std::cout << "void " << function_name << "() " << std::endl;
        std::cout << "{" << std::endl;
        std::cout << "  std::cout << \"Hello from: " << string << "\" << std::endl;" << std::endl;
        std::cout << "}" << std::endl;
        std::cout << std::endl;
        string_map.emplace(string, function_name);
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
    std::cout << "#include <iostream>" << std::endl;
    std::cout << "#include <map>" << std::endl;
    for_each(iter, end, printer);

    // Print main function.
    std::cout << "int main(int argc, char ** argv)" << std::endl;
    std::cout << "{" << std::endl;

    std::cout << "  std::map<std::string,void (*) (void)> func_map;" << std::endl;

    for(auto pair : string_map) {
        std::cout << "  func_map.emplace(\"" << pair.first << "\"," << pair.second << ");" << std::endl;
    }

    std::cout << "  std::string token_name;" << std::endl;
    std::cout << "  std::cout << \"Enter a protocol token:\" << std::endl;" << std::endl;
    std::cout << "  while(std::cin >> token_name) {" << std::endl;
    std::cout << "      auto pointer = func_map.find(token_name);" << std::endl;
    std::cout << "      if (pointer == func_map.end()) {" << std::endl;
    std::cout << "          std::cout << \"Don't know what to do about: \" << token_name << \", try another.\" << std::endl;" << std::endl;
    std::cout << "      } else {" << std::endl;
    std::cout << "          (*pointer).second();" << std::endl;
    std::cout << "      }" << std::endl;
    std::cout << "  }" << std::endl;

    std::cout << "}" << std::endl;
}
