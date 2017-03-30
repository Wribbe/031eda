#ifndef DATABASEINTERFACE_H
#define DATABASEINTERFACE_H

#include "article.h"
#include <string>

using ID = uint32_t;

class DatabaseInterface {
public:
    virtual ~DatabaseInterface() {};
    //Parameters
    virtual void create_newsgroup(std::string title, ID ng_id) = 0;
    //parameters
    virtual void save_article(ID ng_id, Article a) = 0;
    //Parameters?
    virtual Article& load_article(ID ng_id, ID a_id) = 0 ;
    //Parameters?
    virtual Article& delete_article(ID ng_id, ID a_id) = 0;
    //Parameters?
    virtual void delete_newsgroup(ID ng_id) = 0;
    //Is this necessary? Should it be sorted by ID or name?
    virtual bool exists(ID ng_id) = 0;
};

#endif
