#include "memorydatabase.h"

MemoryDatabase::MemoryDatabase()
{
    /* Empty constructor. */
}

void MemoryDatabase::create_newsgroup(std::string title, ID ng_id) {
    for (auto it = database.begin(); it != database.end(); ++it) {
        if ((*it).second.title().compare(title) == 0) {
            return;
        }
    }
    if (database.find(ng_id) == database.end()) {
        NewsGroup ng(title, ng_id);
        database[ng_id] = ng;
    }
}

void MemoryDatabase::save_article(ID ng_id, Article a) {
    database[ng_id].add(a);
}

Article& MemoryDatabase::load_article(ID ng_id, ID a_id) {
    return database[ng_id].find(a_id);
}

Article& MemoryDatabase::delete_article(ID ng_id, ID a_id) {
    return database[ng_id].delete_article(a_id);
}

void MemoryDatabase::delete_newsgroup(ID ng_id) {
    database.erase(ng_id);
}

bool MemoryDatabase::exists(ID ng_id) {
    if (database.find(ng_id) != database.end()) { return true; }
    else { return false; }
}
