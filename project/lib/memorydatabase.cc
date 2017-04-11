#include "memorydatabase.h"

MemoryDatabase::MemoryDatabase() : newsgroup_ID(0) {}

bool MemoryDatabase::create_newsgroup(std::string title) {
    for (auto it = database.begin(); it != database.end(); ++it) {
        if ((*it).second.title().compare(title) == 0) {
            return false;
        }
    }
    ++newsgroup_ID;
    NewsGroup ng(title, newsgroup_ID);
    database[newsgroup_ID] = ng;
    return true;
}

void MemoryDatabase::save_article(ID ng_id, std::string &a_title, std::string &a_author, std::string &a_text) {
    database[ng_id].save_article(a_title, a_author, a_text);
}

Article &MemoryDatabase::load_article(ID ng_id, ID a_id) {
    return database[ng_id].find_article(a_id);
}

Article &MemoryDatabase::delete_article(ID ng_id, ID a_id) {
    return database[ng_id].delete_article(a_id);
}

void MemoryDatabase::delete_newsgroup(ID ng_id) {
    database.erase(ng_id);
}

bool MemoryDatabase::exists(ID ng_id) {
    if (database.find(ng_id) != database.end()) { return true; }
    else { return false; }
}

NewsGroup &MemoryDatabase::get_newsgroup(ID ng_id) {
    return database[ng_id];
}

std::vector <NewsGroup> MemoryDatabase::get_newsgroups() {
    std::vector <NewsGroup> newsgroups;
    for (auto it = database.begin(); it != database.end(); ++it) {
        newsgroups.push_back((*it).second);
    }
    return newsgroups;
}
