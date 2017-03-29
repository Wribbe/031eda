#ifndef DISKDATABASE_H
#define DISKDATABASE_H

#include "databaseinterface.h"
#include <map>
#include <vector>

class DiskDatabase : public DatabaseInterface {
public:
    DiskDatabase();
    void save_article(ID ng_id, Article a);
    //Parameters?
    Article load_article(ID ng_id, ID a_id);
    //Parameters?
    Article delete_article(ID ng_id, ID a_id);
    //Param?
    void delete_newsgroup(ID ng_id);
    //Is this necessary? Should it be sorted by ID or name?
    bool exists(ID ng_id);
private:
    std::map<ID, std::vector<Article>> database;
};

#endif
