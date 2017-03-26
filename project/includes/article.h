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

Article article_from_binary(std::string& binary_string, uint32_t bits=32);

std::ostream& operator<<(std::ostream& stream, Article& article);

#endif
