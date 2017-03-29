#include "newsgroup.h"

NewsGroup::NewsGroup(std::string title, ID id) : _title(title), _id(id) {}

Article& NewsGroup::find(ID _id) {
    for (Article a : articles) {
        if (a.id() == _id) { return a; }
    }
}

void NewsGroup::add(Article& _a) {
    articles.push_back(a);
}

std::string NewsGroup::title() {
    return _title;
}

ID NewsGroup::id() {
    return _id;
}

Article NewsGroup::delete_article(ID _id) {
    for (auto it = articles.begin(); it != articles.end(); ++it) {
        if (it->id() == _id) {
            Article a = *it;
            articles.erase(it);
            return a;
        }
    }
}
