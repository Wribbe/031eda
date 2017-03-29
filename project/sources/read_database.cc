#include <dirent.h>
#include <iostream>

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
    DIR * dirp = opendir("inputs/database");
    if (dirp == NULL) {
        std::cerr << "NO SUCH FOLDER!" << std::endl;
    }
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        if (is_newsgroup_file(dp)) {
            std::cout << dp->d_name << std::endl;
        }
    }
    (void)closedir(dirp);
}
