#include "diskdatabase.h"
#include <exception>
#include <sqlite3.h>

using namespace std;

DiskDatabase::DiskDatabase() : newsgroup_ID(0) { //not done
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("usenet.db", &db);

    if (rc) {
        fprintf(stdout, "Can't open database: %s\n", sqlite3_errmsg(db));
        cout << "FAIL" << endl;
    } else {
        fprintf(stdout, "Opened database successfully\n");
        cout << "WIN" << endl;
    }
//    sqlite3_close(db);
}

bool DiskDatabase::create_newsgroup(std::string title) {
    return false;
}

void save_article(ID ng_id, Article a) {
}

Article &DiskDatabase::load_article(ID ng_id, ID a_id) {

}

Article &DiskDatabase::delete_article(ID ng_id, ID a_id) {

}

void DiskDatabase::delete_newsgroup(ID ng_id) {
}

bool DiskDatabase::exists(ID ng_id) {
}

NewsGroup &DiskDatabase::get_newsgroup(ID ng_id) {
}

std::vector <NewsGroup> DiskDatabase::get_newsgroups() {

}
