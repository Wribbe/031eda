//
// Created by Jonathan Schurmann on 4/12/17.
//

#include "diskdatabase.h"
#include "article.h"
#include "newsgroup.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void print_ngs(vector <NewsGroup> &ngs) {
    for (size_t i = 0; i < ngs.size(); ++i) {
        std::cout << ngs[i].id() << ":" << ngs[i].title() << "\n";
    }
    std::cout << '\n';
}


void print_ng(NewsGroup &ng) {
    std::cout << ng.id() << ":" << ng.title() << endl;
}

void print_articles(vector <Article> &art) {
    for (size_t i = 0; i < art.size(); ++i) {
        std::cout << art[i].id() << ":" << art[i].title() << ":" << art[i].author() << ":" << art[i].text() << endl;
    }
    std::cout << '\n';
}

void print_article(Article &art) {
    std::cout << art.id() << ":" << art.title() << ":" << art.author() << ":" << art.text() << endl;
}

int main() {
    system("sqlite3 usenet.db < setup_db.sql");
    DiskDatabase md;
    string author("Nils");
    string text("Worthless text");
    string title("Wonderful title");

    string author2("Nils2");
    string text2("Worthless text2");
    string title2("Wonderful title2");

    string author3("Nils3");
    string text3("Worthless text3");
    string title3("Wonderful title3");

    Article article1(1, title, author, text);
    Article article2(2, title2, author2, text2);
    Article article3(3, title3, author3, text3);


    vector <NewsGroup> ngs = md.get_newsgroups();
    print_ngs(ngs);

    cout << "get newsgroup 1" << endl;
    NewsGroup ng = md.get_newsgroup(1);
    print_ng(ng);
    cout << endl;

    cout << "creating newsgroups" << endl;

    md.create_newsgroup("My Newsgroup");
    md.create_newsgroup("Another newsgroup");
    md.create_newsgroup("My Newsgroup");
    md.create_newsgroup("Different newsgroup");


    ngs = md.get_newsgroups();
    print_ngs(ngs);

    bool exists = md.exists(8);
    cout << "Newsgroup with id 8 exists: " << exists << endl;
    exists = md.exists(9);
    cout << "Newsgroup with id 9 exists: " << exists << endl;
    cout << "creating newsgroups" << endl;


    cout << "deleting previously created newsgroups" << endl;
    for (size_t i = 5; i <= ngs.size(); ++i) {
        md.delete_newsgroup(i);
    }

    ngs = md.get_newsgroups();
    print_ngs(ngs);


    Article art = md.load_article(1, 1);
    print_article(art);
    art = md.load_article(1, 2);
    print_article(art);
    cout << endl;


    cout << "creating article" << endl;
    md.save_article(1, title, author, text);
    art = md.load_article(1, 4);
    print_article(art);


//    system("sqlite3 usenet.db < setup_db.sql");
//    cout << md.delete_article(85, 3) << endl;
}
