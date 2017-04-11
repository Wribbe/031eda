#include "newsgroup.h"

NewsGroup::NewsGroup(std::string title, ID id) : _title(title), _id(id), article_ID(0) {}

Article& NewsGroup::find_article(ID _id) {
    for (Article& a : articles) {
        if (a.id() == _id) { return a; }
    }
    return null_article;
}

bool NewsGroup::article_exists(ID _id) {
    for (Article& a : articles) {
        if (a.id() == _id) { return true; }
    }
    return false;
}

void NewsGroup::save_article(std::string& a_title, std::string& a_author, std::string& a_text) {
    ++article_ID;
    Article a(article_ID, a_title, a_author, a_text);
    articles.push_back(a);
}

std::vector<Article>& NewsGroup::get_articles() {
    return articles;
}

std::string NewsGroup::title() {
    return _title;
}

ID NewsGroup::id() {
    return _id;
}

Article& NewsGroup::delete_article(ID _id) {
    for (auto it = articles.begin(); it != articles.end(); ++it) {
        if (it->id() == _id) {
            Article& a = *it;
            articles.erase(it);
            return a;
        }
    }
    return null_article;
}
