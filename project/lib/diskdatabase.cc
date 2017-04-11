#include "diskdatabase.h"
#include <exception>
#include <dirent>
#include <sys/stat>
#include <sys/types>

using namespace std;

DiskDatabase::DiskDatabase() : newsgroup_ID(0) { //not done
    /*DIR *dir;
    if ((dir = opendir(".")) == NULL) {
        perror("Couldn't open '.'");
        return;
    }*/

}

bool DiskDatabase::create_newsgroup(std::string title) { //not done
    if (database.at(ng_id) == database.end()) {
        database[ng_id] = new NewsGroup(title, ng_id);
    }
    return false;
}

void DiskDatabase::save_article(ID ng_id, std::string& a_title, std::string& a_author, std::string& a_text) { //not done
    database[ng_id].save_article(a_title, a_author, a_text);
}

Article& DiskDatabase::load_article(ID ng_id, ID a_id) { //done
    //Try: If there isn't a ng_id we throw e to server
    try {
        return database[ng_id].find_article(a_id);
    } catch (std::exception& e) {
        throw e;
        return;
    }
}

Article& DiskDatabase::delete_article(ID ng_id, ID a_id) {//not done
    try {
        return database[ng_id].delete_article(a_id);
    } catch (std::exception& e) {
        throw e;
        return;
    }

}

void DiskDatabase::delete_newsgroup(ID ng_id) { //not done
    database.erase(ng_id);

}

bool DiskDatabase::exists(ID ng_id) { //done
    if (database.at(ng_id) != database.end()) { return true; }
    else { return false; }
}

NewsGroup& DiskDatabase::get_newsgroup(ID ng_id) {
    return database[ng_id];
}

std::vector<NewsGroup> DiskDatabase::get_newsgroups() {
    std::vector<NewsGroup> newsgroups;
    for(auto it = database.begin(); it != database.end(); ++it) {
        newsgroups.push_back((*it).second);
    }
    return newsgroups;
}
