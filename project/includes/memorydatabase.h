#ifndef MEMORYDATABASE_H
#define MEMORYDATABASE_H

#include "databaseinterface.h"
#include <map>
#include <vector>

class MemoryDatabase : public DatabaseInterface {
public:
    MemoryDatabase();
    void save_article(ID ng_id, Article a);
    //Parameters?
    Article load_article(ID ng_id, ID a_id);
    //Parameters?
    Article delete_article(ID ng_id, ID a_id);
    //Is this necessary? Should it be sorted by ID or name?
    bool exists(ID ng_id);
private:
    std::map<ID, std::vector<Article>> database;
};

#endif
