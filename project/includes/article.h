#ifndef ARTICLE_H
#define ARTICLE_H

#include <iostream>
#include <ostream>
#include <string>

#include "encoding.h"

class Article
{
public:
    /* Friends. */
    friend std::ostream& operator<<(std::ostream& stream, Article& article);
    friend std::istream& operator>>(std::istream& stream, Article& article);
    /* Constructors. */
    Article();
    Article(std::istream& encoded_stream);
    Article(
            uint32_t id,
            std::string& title,
            std::string& author,
            std::string& text
           );
    /* Public methods. */
    std::string encode(uint32_t base=base,
                       uint32_t chunk_size=bitsize_packtype_t);
    void decode(std::istream& stream,
                uint32_t base=base,
                uint32_t chunk_size=bitsize_packtype_t);
    /* Getters. */
    uint32_t id();
    std::string title();
    std::string author();
    std::string text();
//private:
    uint32_t _id;
    std::string _title;
    std::string _author;
    std::string _text;
};

std::ostream& operator<<(std::ostream& stream, Article& article);
std::istream& operator>>(std::istream& stream, Article& article);

static Article null_article;

#endif
