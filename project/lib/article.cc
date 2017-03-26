#include <sstream>

#include "article.h"

Article::Article(uint32_t id) :
    id(id),
    title(""),
    author(""),
    text("")
    /* Default constructor for Article. */
{
    /* Empty */
}

Article::Article(uint32_t id,
                 std::string title,
                 std::string author,
                 std::string text) :
    id(id),
    title(title),
    author(author),
    text(text)
    /* Specified constructor for Article. */
{
    /* Empty */
}

std::string to_binary_string(uint32_t number)
{
    std::stringstream stream;

    uint32_t mask = 0xff000000;

    for (size_t i=0; i<sizeof(number); ++i) { /* 0,1,2,3 */
        uint32_t current = (number & mask) >> (8*(3-i)); /* 3,2,1,0 */
        uint32_t divisor = 0x100; // 256.
        while (divisor > 0) {
            uint32_t result = current / divisor;
            stream << result;
            current -= result ? divisor : 0; // Only subtract on 1.
            divisor >>= 1; // Next lower power of 2.
        }
        mask >>= 8; // Move "ff" two 'steps' to the right.
    }
    return stream.str();
}

std::string serialize(std::string string)
{
    std::stringstream stream;
    uint32_t length = sizeof(string);
    stream << to_binary_string(length);
    uint32_t current = 0;
    uint8_t shifts = 0;
    for (size_t i=0; i<length; ++i) {
        current += string[i];
        current <<= 8;
        shifts++;
        if (shifts == 4) {
            stream << to_binary_string(current);
            current = 0;
            shifts = 0;
        }
    }
    if (current > 0) {
        stream << to_binary_string(current);
    }
    return stream.str();
}

std::ostream& operator<<(std::ostream& stream, Article& article)
{
    stream << to_binary_string(article.id);
    return stream;
}
