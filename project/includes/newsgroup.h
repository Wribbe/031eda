#ifndef NEWSGROUP_H
#define NEWSGROUP_H

#include "article.h"
#include <string>
#include <vector>

using ID = uint32_t;

class NewsGroup {
public:
    NewsGroup(std::string _title, ID _id);

    NewsGroup() : NewsGroup("empty", 0) {};

    Article &find_article(ID _id);

    bool article_exists(ID _id);

    void save_article(std::string &a_title, std::string &a_author, std::string &a_text);

    Article &delete_article(ID _id);

    std::vector <Article> &get_articles();

    ID id();

    std::string title();

private:
    std::vector <Article> articles;
    std::string _title;
    ID _id;
    ID article_ID;
};

#endif
