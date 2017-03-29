#ifndef DATABASEINTERFACE_H
#define DATABASEINTERFACE_H

#include "article.h"
#include <string>

class DatabaseInterface {
    using ID = uint32_t;
public:
    virtual ~DatabaseInterface();
    //Parameters
    virtual void create_newsgroup(std::string title, ID ng_id);
    //parameters
    virtual void save_article(ID ng_id, Article a);
    //Parameters?
    virtual Article& load_article(ID ng_id, ID a_id);
    //Parameters?
    virtual Article& delete_article(ID ng_id, ID a_id);
    //Parameters?
    virtual void delete_newsgroup(ID ng_id);
    //Is this necessary? Should it be sorted by ID or name?
    virtual bool exists(ID ng_id);
};

#endif
