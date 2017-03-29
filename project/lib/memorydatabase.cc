#include "memorydatabase.h"
#include <exception>

MemoryDatabase::MemoryDatabase() {}

void MemoryDatabase::create_newsgroup(std::string title, ID ng_id) {
    if (database.at(ng_id) == database.end()) {
        database[ng_id] = new NewsGroup(title, ng_id);
    }
}

void MemoryDatabase::save_article(ID ng_id, Article a) {
    database[ng_id].add(a);
}

Article& MemoryDatabase::load_article(ID ng_id, ID a_id) {
    //Try: If there isn't a ng_id we throw e to server
    try {
        return database[ng_id].find(a_id);
    } catch (std::exception& e) {
        throw e;
        return;
    }
}

Article& MemoryDatabase::delete_article(ID ng_id, ID a_id) {
    try {
        return database[ng_id].delete_article(a_id);
    } catch (std::exception& e) {
        throw e;
        return;
    }
}

void MemoryDatabase::delete_newsgroup(ID ng_id) {
    database.erase(ng_id);
}

bool MemoryDatabase::exists(ID ng_id) {
    if (database.at(ng_id) != database.end()) { return true; }
    else { return false; }
}
