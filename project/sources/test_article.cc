#include <iostream>
#include <sstream>

#include "article.h"

void test(const std::string& message,
          const std::string& a,
          const std::string& b)
{
    std::string pos = "True";
    std::string neg = "False";
    std::cout << message << ": ";
    if (a.compare(b) == 0) {
        std::cout << pos;
    } else {
        std::cout << neg;
    }
    std::cout << std::endl;
}


int main()
{
    uint32_t id = 82;
    std::string title = "This is title.";
    std::string author = "Test author.";
    std::string text = "This is a multiline\ntext snippet\nthat is the body of the article.";

    std::stringstream stream;

    Article article(id,title,author,text);
    stream << article;

    std::cout << stream.str() << std::endl;
    Article decoded(stream);

    std::cout << "id: " << decoded.id() << std::endl;
    std::cout << "title: " << decoded.title() << std::endl;
    std::cout << "author: " << decoded.author() << std::endl;
    std::cout << "text: " << decoded.text() << std::endl;

    test("Article has same title", article.title(), decoded.title());
    test("Article has same author", article.author(), decoded.author());
    test("Article has same text", article.text(), decoded.text());
    test("Article has same id", std::to_string(article.id()), std::to_string(decoded.id()));
}
