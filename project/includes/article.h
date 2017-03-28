#ifndef ARTICLE_H
#define ARTICLE_H

#include <iostream>
#include <ostream>
#include <string>

#define BASE 64
#define CHUNK_SIZE 32

using packtype_t = uint64_t;

size_t bitsize_char = 8;
size_t bitsize_packtype_t = sizeof(packtype_t)*8;
size_t chars_in_packtype = bitsize_packtype_t/bitsize_char;


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
    /* Public methods. */
    std::string encode(packtype_t base=BASE);
    /* Public getters. */
    const uint32_t& id();
    const std::string& title();
    const std::string& author();
    const std::string& text();
private:
    uint32_t pid;
    std::string ptitle;
    std::string pauthor;
    std::string ptext;
};

Article article_from_encoded(std::string& binary_string,
                             uint32_t bits=CHUNK_SIZE,
                             uint32_t base=BASE);

std::ostream& operator<<(std::ostream& stream, Article& article);

#endif
