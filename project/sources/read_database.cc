#include <dirent.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

bool is_newsgroup_file(struct dirent * dp)
{
    std::string name = std::string(dp->d_name);
    if (name.find("newsgroup") != std::string::npos) {
        return true;
    }
    return false;
}

int main(void)
{
    std::string database_folder = "inputs/database";
    DIR * dirp = opendir(database_folder.c_str());

    if (dirp == NULL) {
        std::cerr << "NO SUCH FOLDER!" << std::endl;
        return EXIT_FAILURE;
    }

    std::vector<std::string> filepaths;

    struct dirent * dp;
    std::stringstream stream;
    while ((dp = readdir(dirp)) != NULL) {
        if (is_newsgroup_file(dp)) {
            // Construct full path.
            stream << database_folder;
            stream << "/";
            stream << dp->d_name;
            filepaths.push_back(stream.str());
            // Reset stream.
            std::stringstream().swap(stream);
        }
    }
    // Close open folder.
    (void)closedir(dirp);
    // Print data from all files.
    std::string line;
    for(std::string file_path : filepaths) {
        std::ifstream file_stream(file_path);
        if (!file_stream.is_open()) {
            std::cerr << "No such file: " << file_path << std::endl;
            return EXIT_FAILURE;
        }
        std::cout << "Printing contents of : " << file_path << ":" << std::endl;
        std::cout << std::endl; // Newline separation.
        while (std::getline(file_stream, line)) {
            std::cout << "   " << line << std::endl;
        }
        std::cout << std::endl;
    }
}
