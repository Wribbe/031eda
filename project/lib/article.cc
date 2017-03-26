#include "article.h"

Article::Article(int id) :
    id(id),
    title(""),
    author(""),
    text("")
    /* Default constructor for Article. */
{
    /* Empty */
}

Article::Article(int id,
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
