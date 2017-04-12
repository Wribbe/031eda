#ifndef DISKDATABASE_H
#define DISKDATABASE_H

#include "databaseinterface.h"
#include <map>
#include <sqlite3.h>

class DiskDatabase : public DatabaseInterface {
public:
    DiskDatabase();

    ~DiskDatabase() {};

    bool create_newsgroup(std::string title);

    void save_article(ID ng_id, std::string &a_title, std::string &a_author, std::string &a_text);

    //Parameters?
    Article &load_article(ID ng_id, ID a_id);

    //Parameters?
    Article &delete_article(ID ng_id, ID a_id);

    //Param?
    void delete_newsgroup(ID ng_id);

    //Is this necessary? Should it be sorted by ID or name?
    bool exists(ID ng_id);

    NewsGroup &get_newsgroup(ID ng_id);

    //
    std::vector <NewsGroup> get_newsgroups();

private:
    sqlite3 *db;
    std::map <ID, NewsGroup> database;
    ID newsgroup_ID;

};

#endif
