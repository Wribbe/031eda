#ifndef MEMORYDATABASE_H
#define MEMORYDATABASE_H

#include "databaseinterface.h"
#include "newsgroup.h"
#include <map>

class MemoryDatabase : public DatabaseInterface {
public:
    MemoryDatabase();
    ~MemoryDatabase() {};
    void create_newsgroup(std::string title, ID ng_id);
    void save_article(ID ng_id, Article a);
    //Parameters?
    Article& load_article(ID ng_id, ID a_id);
    //Parameters?
    Article& delete_article(ID ng_id, ID a_id);
    //Param?
    void delete_newsgroup(ID ng_id);
    //Is this necessary? Should it be sorted by ID or name?
    bool exists(ID ng_id);
private:
    std::map<ID, NewsGroup> database;
};

#endif
