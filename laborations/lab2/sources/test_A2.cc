#include <iostream>
#include <string>
#include "dictionary.h"

int main(void)
    /* Try to create a dictionary. */
{
    std::string faulty_path = "this_file_does_not_exist.txt";
    Dictionary faulty_dict(faulty_path);
    if (faulty_dict.is_empty()) {
        std::cout << "No such file: <"<< faulty_path <<"> " <<  std::endl;
    }

    Dictionary default_dict;
}
