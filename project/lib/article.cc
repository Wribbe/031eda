#include "article.h"

Article::Article(uint32_t id,
                 std::string& title,
                 std::string& author,
                 std::string& text) :
    _id(id),
    _title(title),
    _author(author),
    _text(text)
{
    /* Empty constructor. */
}

Article::Article(std::istream& encoded_stream)
{
    encoded_stream >> *this;
}

uint32_t Article::id()
{
    return _id;
}
std::string Article::title()
{
    return _title;
}
std::string Article::author()
{
    return _author;
}
std::string Article::text()
{
    return _text;
}

/* Encoding functions. */
std::string Article::encode(uint32_t base, uint32_t chunk_size)
{
    std::stringstream stream;
    stream << libencode(_id, base, chunk_size);
    stream << libencode_with_prefix(_title, base, chunk_size);
    stream << libencode_with_prefix(_author, base, chunk_size);
    stream << libencode_with_prefix(_text, base, chunk_size);
    return stream.str();
}

std::ostream& operator<<(std::ostream& stream, Article& article)
{
    stream << article.encode();
    return stream;
}

/* Decoding functions. */
void Article::decode(std::istream& istream, uint32_t base, uint32_t chunk_size)
{
    _id = libdecode_value(istream, base, chunk_size);
    _title = libdecode_string(istream, base, chunk_size);
    _author = libdecode_string(istream, base, chunk_size);
    _text = libdecode_string(istream, base, chunk_size);
}

std::istream& operator>>(std::istream& stream, Article& article)
{
    article.decode(stream);
    return stream;
}
