#include "diskdatabase.h"
#include <exception>

using namespace std;

DiskDatabase::DiskDatabase() {}

void DiskDatabase::save_article(ID ng_id, Article a) {

}

Article DiskDatabase::load_article(ID ng_id, ID a_id) {
    return NULL;
}

Article DiskDatabase::delete_article(ID ng_id, ID a_id) {
    return NULL;
}

void DiskDatabase::delete_newsgroup(ID ng_id) {

}

bool DiskDatabase::exists(ID ng_id) {
    if (database.at(ng_id) != database.end()) { return true; }
    else { return false; }
}
