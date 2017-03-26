#include <iostream>
#include <sstream>

#include "article.h"

int main()
{
    uint32_t id = 1;
    std::string title = "This is title.";
    std::string author = "Test author.";
    std::string text = "This is a multiline\ntext snippet\nthat is the body of the article.";

    std::stringstream stream;

    Article article(id,title,author,text);
    stream << article;

    std::string encoded_article = stream.str();
    std::cout << encoded_article << std::endl;

    article_from_binary(encoded_article);
}
