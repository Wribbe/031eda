#include <iostream>

#include "article.h"

int main()
{
    unsigned int id = 1;
    std::string title = "This is title.";
    std::string author = "Test author.";
    std::string text = "This is a multiline\ntext snippet\nthat is the body of the article.";

    Article article(id,title,author,text);
}
