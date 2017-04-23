#ifndef DATABASEINTERFACE_H
#define DATABASEINTERFACE_H

#include "article.h"
#include "newsgroup.h"
#include <string>
#include <vector>

using ID = uint32_t;

class DatabaseInterface {
public:
    virtual ~DatabaseInterface() {};
    //Parameters
    virtual bool create_newsgroup(std::string title) = 0;
    //parameters
    virtual void save_article(ID ng_id, std::string& a_title, std::string& a_author, std::string& a_text) = 0;
    //Parameters?
    virtual Article& load_article(ID ng_id, ID a_id) = 0;

    virtual std::vector<Article>& load_articles(ID ng_id) = 0;
    //Parameters?
    virtual Article& delete_article(ID ng_id, ID a_id) = 0;
    //Parameters?
    virtual void delete_newsgroup(ID ng_id) = 0;
    //Is this necessary? Should it be sorted by ID or name?
    virtual bool newsgroup_exists(ID ng_id) = 0;

    virtual bool article_exists(ID ng_id, ID a_id) = 0;

    virtual NewsGroup& get_newsgroup(ID ng_id) = 0;
    //
    virtual std::vector<NewsGroup> get_newsgroups() = 0;
};

#endif
