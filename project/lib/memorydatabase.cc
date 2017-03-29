#include "memorydatabase.h"
#include <exception>

using namespace std;

MemoryDatabase::MemoryDatabase() {}

void MemoryDatabase::save_article(ID ng_id, Article a) {
    if (database.at(ng_id) != database.end()) {
        database[ng_id].push_back(a);
    } else {
        vector<Article> new_ng;
        new_ng.push_back(a);
        database[ng_id] = new_ng;
    }
}

Article MemoryDatabase::load_article(ID ng_id, ID a_id) {
    //Try: If there isn't a ng_id we throw e to server
    try {
        vector<Article> articles = database[ng_id];
        for (Article a : articles) {
            if(a.get_ID() == a_id) {
                return a;
            }
        }
    } catch (exception& e) {
        throw e;
        return NULL; //NULL?
    }
}

Article MemoryDatabase::delete_article(ID ng_id, ID a_id) {
    try {
        vector<Article> articles = database[ng_id]; //Need reference or not?
        for (auto it = articles.begin(); it != articles.end(); ++it) {
            if(it->get_ID() == a_id) {
                Article ret = *it;
                articles.erase(it);
                return *ret;z
            }
        }
    } catch (exception& e) {
        throw e;
        return NULL; //NULL?
    }
}

void MemoryDatabase::delete_newsgroup(ID ng_id) {
    database.erase(ng_id);
}

bool MemoryDatabase::exists(ID ng_id) {
    if (database.at(ng_id) != database.end()) { return true; }
    else { return false; }
}
