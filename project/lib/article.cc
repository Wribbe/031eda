#include <iterator>
#include <sstream>

#include "article.h"

Article::Article(uint32_t id) :
    pid(id),
    ptitle(""),
    pauthor(""),
    ptext("")
    /* Default constructor for Article. */
{
    /* Empty */
}

const uint32_t& Article::id() {
    return pid;
}

const std::string& Article::title() {
    return ptitle;
}
const std::string& Article::author() {
    return pauthor;
}
const std::string& Article::text() {
    return ptext;
}

Article::Article(uint32_t id,
                 std::string title,
                 std::string author,
                 std::string text) :
    pid(id),
    ptitle(title),
    pauthor(author),
    ptext(text)
    /* Specified constructor for Article. */
{
    /* Empty */
}

std::string num_to_binary(uint32_t number, size_t bits=32)
{
    std::stringstream stream;

    uint32_t divisor = 1 << (bits-1);

    while (divisor > 0) {
        uint32_t result = number/divisor;
        if (result) {
            stream << 1;
            number -= divisor;
        } else {
            stream << 0;
        }
        divisor >>= 1; // goto next lower power of 2.
    }
    return stream.str();
}

size_t bitsize_char = 8;
size_t bitsize_uint32_t = 32;
size_t chars_in_uint32 = bitsize_uint32_t/bitsize_char;

std::string binary_string(std::string string)
{
    std::stringstream stream;

    uint32_t current = 0;
    uint32_t shifts = 0;
    size_t length = string.length();

    for(size_t i=0; i<length; ++i) {
        if (i%chars_in_uint32 > 0) {
            current <<= bitsize_char;
            shifts++;
        }
        current += string[i];
        if (shifts == chars_in_uint32-1) {
            stream << num_to_binary(current);
            current = 0;
            shifts = 0;
        }
    }
    if (current > 0) {
        stream << num_to_binary(current);
    }
    return stream.str();
}

std::string binary_with_length_prefix(std::string string)
{
    std::stringstream stream;
    stream << num_to_binary(string.length());
    stream << binary_string(string);
    return stream.str();
}

std::ostream& operator<<(std::ostream& stream, Article& article)
{
    stream << num_to_binary(article.id());
    stream << binary_with_length_prefix(article.title());
    stream << binary_with_length_prefix(article.author());
    stream << binary_with_length_prefix(article.text());
    return stream;
}

using bin_iter = std::string::iterator;

uint32_t get_prefix(bin_iter& p1, bin_iter& p2, uint32_t bits=32)
{
    int base = 2;
    uint32_t prefix = std::stoul(std::string(p1,p2),nullptr,base);
    p1 += bits;
    p2 += bits;
    return prefix;
}

uint32_t num_32chunks_to_read(uint32_t string_length)
{
    uint32_t chunks = string_length/chars_in_uint32;
    if (string_length%chars_in_uint32) {
        chunks++;
    }
    return chunks;
}

std::string chunks_to_string(bin_iter& p1, bin_iter& p2, size_t chunks)
{
    std::stringstream stream;
    uint32_t stream_base = 2;
    for (size_t i=0; i<chunks; ++i) {
        while(p1 != p2) {
            uint32_t number = std::stoul(std::string(p1,p1+bitsize_char),
                                         nullptr,
                                         stream_base);
            if (number > 0) { // Ignore null values.
                stream << static_cast<char>(number);
            }
            p1 += bitsize_char;
        }
        p2 += bitsize_uint32_t;
    }
    return stream.str();
}

Article article_from_binary(std::string& binary_string, uint32_t bits)
{
    bin_iter p1 = binary_string.begin();
    bin_iter p2 = binary_string.begin()+bits;

    // Decode id.
    uint32_t id = get_prefix(p1,p2);
    // Decode title length.
    uint32_t length_title = get_prefix(p1,p2);
    // Get number of 32-bit chunks to read.
    uint32_t chunks = num_32chunks_to_read(length_title);
    // Decode title chunks.
    std::string title = chunks_to_string(p1,p2,chunks);
    // Decode author chunks.
    chunks = num_32chunks_to_read(get_prefix(p1,p2));
    std::string author = chunks_to_string(p1,p2,chunks);
    // Decode text chunks.
    chunks = num_32chunks_to_read(get_prefix(p1,p2));
    std::string text = chunks_to_string(p1,p2,chunks);

    return Article(id,title,author,text);
}
