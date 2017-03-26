#include <iostream>
#include <string>

class Article
{
public:
    /* Constructors. */
    Article(int id);
    Article(
            int id,
            std::string title,
            std::string author,
            std::string text
           );
private:
    int id;
    std::string title;
    std::string author;
    std::string text;
};
