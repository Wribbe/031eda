#ifndef NEWSGROUP_H
#define NEWSGROUP_H

#include "article.h"
#include <string>
#include <vector>

using ID = uint32_t;

class NewsGroup {
public:
    NewsGroup(std::string _title, ID _id);
    Article& find(ID _id);
    void add(Article& _a);
    Article delete_article(ID _id);
    ID id();
    std::string title();
private:
    std::vector<Article> articles;
    std::string _title;
    ID _id;
};

#endif
