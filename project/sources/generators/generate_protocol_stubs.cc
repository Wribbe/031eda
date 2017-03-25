// Input: includes/protocol.h
// Output: demo_hello_from_protocol_tokens.cc
#include "print_functions.h"

std::map<std::string,std::string> string_map;

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

int main(int argc, char ** argv)
{
    if (argc < 2) {
        std::string exec_path = std::string(argv[0]);
        std::string exec_name = exec_path.substr(exec_path.find_last_of('/')+1);
        std::cerr << "Usage: ./" << exec_name << " protocol.h" << std::endl;
        return EXIT_FAILURE;
    }

    std::vector<std::string> lines = get_lines(argv[1]);
    println("// THIS FILE IS GENERATED, DO NOT EDIT BY HAND.");
    std::vector<std::string> includes = std::vector<std::string>{
                                            "<iostream>",
                                            "<map>",
                                            "\"print_functions.h\"",
                                        };
    add_includes(includes);
    hello_function_printer(lines);

    // Print main function.
    println("int main()");
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
