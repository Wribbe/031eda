#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>

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

std::map<std::string,std::string> string_map;

template <typename T>
void print(const T& string)
    /* Print string to std::cout without newline. */
{
    std::cout << string;
}

template <typename T>
void println(const T& string)
    /* Print string to std::cout with newline. */
{
    print(string);
    std::cout << std::endl;
}


template <typename T>
void hello_function_printer(std::vector<T>& lines)
{
    for (T string : lines) {
        std::string token = "=";
        if (find(token,string)) {
            split(string, token);
            strip(string);
            std::string lower(string);
            std::transform(string.begin(), string.end(),lower.begin(),::tolower);
            std::string function_name = "f_" + lower;
            println("void " + function_name + "() ");
            println("{");
            println("  println(\"Hello from: "+ string + "\");");
            println("}");
            println("");
            string_map.emplace(string, function_name);
        }
    }
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

void add_includes(std::vector<std::string> libs)
    /* Print libraries that should be included. */
{
    for (std::string lib : libs) {
        println("#include <" + lib + ">");
    }
    println("");
}


int main(int argc, char ** argv)
{
    if (argc < 2) {
        std::string exec_path = std::string(argv[0]);
        std::string exec_name = exec_path.substr(exec_path.find_last_of('/')+1);
        std::cerr << "Usage: ./" << exec_name << " protocol.h" << std::endl;
        return EXIT_FAILURE;
    }

    std::vector<std::string> lines = get_lines(argv[1]);
    std::vector<std::string> includes = std::vector<std::string>{
                                            "iostream",
                                            "map",
                                        };
    add_includes(includes);
    hello_function_printer(lines);

    // Print main function.
    println("int main(int argc, char ** argv)");
    println("{");
    println("  std::map<std::string,void (*) (void)> func_map;");

    for(auto pair : string_map) {
        println("  func_map.emplace(\"" + pair.first + "\"," + pair.second + ");");
    }

    println("  std::string token_name;");
    println("  std::cout << \"Enter a protocol token:\" << std::endl;");
    println("  while(std::cin >> token_name) {");
    println("    auto pointer = func_map.find(token_name);");
    println("    if (pointer == func_map.end()) {");
    println("        println(\"Don't know what to do about: \" + token_name + \", try another.\");");
    println("    } else {");
    println("        (*pointer).second();");
    println("    }");
    println("  }");
    println("}");
}
