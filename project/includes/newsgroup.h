#ifndef NEWSGROUP_H
#define NEWSGROUP_H

#include "article.h"
#include <string>
#include <vector>

class NewsGroup {
    using ID = uint32_t;
public:
    NewsGroup(std::string _title, ID _id);
    Article& find(ID _id);
    void add(Article& _a);
    Article delete_article(ID _id);
private:
    std::vector<Article> articles;
    std::string title;
    ID id;
};

#endif
