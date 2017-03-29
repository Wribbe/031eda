#include "diskdatabase.h"
#include <exception>
#include <dirent>
#include <sys/stat>
#include <sys/types>

using namespace std;

DiskDatabase::DiskDatabase() { //not done
    DIR *dir;
    if ((dir = opendir(".")) == NULL) {
        perror("Couldn't open '.'");
        return;
    }

}

void DiskDatabase::create_newsgroup(std::string title, ID ng_id) { //not done
    if (database.at(ng_id) == database.end()) {
        database[ng_id] = new NewsGroup(title, ng_id);
    }

}

void DiskDatabase::save_article(ID ng_id, Article a) { //not done
    database[ng_id].add(a);

}

Article& DiskDatabase::load_article(ID ng_id, ID a_id) { //done
    //Try: If there isn't a ng_id we throw e to server
    try {
        return database[ng_id].find(a_id);
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
