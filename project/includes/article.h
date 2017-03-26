#ifndef ARTICLE_H
#define ARTICLE_H

#include <iostream>
#include <ostream>
#include <string>

class Article
{
public:
    friend std::ostream& operator<<(std::ostream& stream, Article& article);
    /* Constructors. */
    Article(uint32_t id);
    Article(
            uint32_t id,
            std::string title,
            std::string author,
            std::string text
           );
private:
    uint32_t id;
    std::string title;
    std::string author;
    std::string text;
};

std::ostream& operator<<(std::ostream& stream, Article& article);

#endif
