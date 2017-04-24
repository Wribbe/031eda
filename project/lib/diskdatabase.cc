#include <exception>
#include <string.h>

#include "diskdatabase.h"
#include "article.h"
#include "newsgroup.h"

using namespace std;

/**
 *
 * @param data Data provided in the 4th argument of sqlite3_exec()
 * @param argc The number of columns in row
 * @param argv An array of strings representing fields in the row
 * @param azColName An array of strings representing column names
 * @return
 */
static int loadArticleCallback(void *data, int argc, char **argv, char **azColName) {
    UNUSED(argc);
    UNUSED(azColName);
    Article *art = static_cast<Article *> (data);
    ID id = atoi(argv[0]);
    std::string title(argv[1]);
    std::string author(argv[2]);
    std::string content(argv[3]);
    *art = Article(id, title, author, content);
    return 0;
}

static int getArticlesCallback(void *data, int argc, char **argv, char **azColName) {
    UNUSED(argc);
    UNUSED(azColName);
    vector <Article> *arts = static_cast< vector <Article> * > (data);
    ID id = atoi(argv[0]);
    std::string title(argv[1]);
    std::string author(argv[2]);
    std::string content(argv[3]);
    Article art(id, title, author, content);
    arts->push_back(art);
    return 0;
}

static int getNewsgroupsCallback(void *data, int argc, char **argv, char **azColName) {
    UNUSED(argc);
    UNUSED(azColName);
    vector <NewsGroup> *ngs = static_cast< vector <NewsGroup> * > (data);
    ID id = atoi(argv[0]);
    std::string title(argv[1]);
    NewsGroup ng(title, id);
    ngs->push_back(ng);
    return 0;
}

static int existsCallback(void *data, int argc, char **argv, char **azColName) {
    UNUSED(argc);
    UNUSED(azColName);
    bool *exists = static_cast<bool *> (data);
    char c = *argv[0];
    if (c == '1') {
        *exists = true;
    }
    return 0;
}

static int getNewsgroupCallback(void *data, int argc, char **argv, char **azColName) {
    UNUSED(argc);
    UNUSED(azColName);
    NewsGroup *ng = static_cast<NewsGroup *> (data);
    ID id = atoi(argv[0]);
    std::string title(argv[1]);
    *ng = NewsGroup(title, id);
    return 0;
}

DiskDatabase::DiskDatabase() : newsgroup_ID(0) { //not done
    int rc;
    rc = sqlite3_open("usenet.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    } else {
        fprintf(stderr, "Opened database successfully\n");
        std::string sql = "PRAGMA foreign_keys = ON";
        sqlite3_exec(db, sql.c_str(), nullptr, 0, nullptr);
    }
//    sqlite3_close(db);
}

bool DiskDatabase::create_newsgroup(std::string title) {
    char *zErrMsg = 0;
    int rc;
    std::string sql = "INSERT INTO newsgroups (title) VALUES ('"
                      + title + "');";
    rc = sqlite3_exec(db, sql.c_str(), nullptr, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return false;
    }
    return true;
}

void DiskDatabase::save_article(ID ng_id, std::string &a_title, std::string &a_author, std::string &a_text) {
    char *zErrMsg = 0;
    int rc;
    std::string sql = "INSERT INTO articles (title, author, content, ng_id) VALUES\n"
                              "('" + a_title + "', '" + a_author + "', '" + a_text + "', '" + std::to_string(ng_id) +
                      "');";
    rc = sqlite3_exec(db, sql.c_str(), nullptr, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
}

Article &DiskDatabase::load_article(ID ng_id, ID a_id) {
    char *zErrMsg = 0;
    int rc;
    Article *art = new Article();
    std::string sql = "SELECT * FROM articles\n"
                              "JOIN newsgroups ON ng_id = id\n"
                              "WHERE ng_id = " + std::to_string(ng_id) + "\n"
                              "AND art_id = " + std::to_string(a_id);
    rc = sqlite3_exec(db, sql.c_str(), loadArticleCallback, art, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    return *art;
}

std::vector <Article> &DiskDatabase::load_articles(ID ng_id) {
    std::vector <Article> *arts = new vector<Article>;
    char *zErrMsg = 0;
    int rc;
    std::string sql = "SELECT * FROM articles\n"
                              "WHERE ng_id = " + std::to_string(ng_id);
    rc = sqlite3_exec(db, sql.c_str(), getArticlesCallback, arts, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    return *arts;
}

Article &DiskDatabase::delete_article(ID ng_id, ID a_id) {
    char *zErrMsg = 0;
    int rc;
    std::string sql = "DELETE FROM articles\n"
                              "WHERE art_id = \n"
                              "(SELECT art_id FROM articles JOIN newsgroups ON ng_id = id WHERE\n"
                              "ng_id = " + std::to_string(ng_id) + " AND \n"
                              "art_id = " + std::to_string(a_id) + " );";
    rc = sqlite3_exec(db, sql.c_str(), nullptr, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    return null_article;
}

void DiskDatabase::delete_newsgroup(ID ng_id) {
    char *zErrMsg = 0;
    int rc;
    std::string sql = "DELETE FROM newsgroups\n"
                              "WHERE id = " + std::to_string(ng_id);
    rc = sqlite3_exec(db, sql.c_str(), nullptr, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
}

bool DiskDatabase::newsgroup_exists(ID ng_id) {
    char *zErrMsg = 0;
    bool def = false;
    bool *exists = &def;
    int rc;
    std::string sql = "SELECT COUNT(*) FROM newsgroups WHERE id = " + std::to_string(ng_id) + ";";
    rc = sqlite3_exec(db, sql.c_str(), existsCallback, exists, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    return *exists;
}

bool DiskDatabase::article_exists(ID ng_id, ID a_id) {
    char *zErrMsg = 0;
    bool def = false;
    bool *exists = &def;
    int rc;
    std::string sql = "SELECT COUNT(*) FROM articles WHERE ng_id = " + std::to_string(ng_id) + "\n"
            "AND art_id = " + std::to_string(a_id);
    rc = sqlite3_exec(db, sql.c_str(), existsCallback, exists, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    return *exists;
}

NewsGroup &DiskDatabase::get_newsgroup(ID ng_id) {
    char *zErrMsg = 0;
    int rc;
    NewsGroup *ng = new NewsGroup("", 0);
    std::string sql = "SELECT * FROM newsgroups\n"
                              "WHERE id = " + std::to_string(ng_id) + ";";
    rc = sqlite3_exec(db, sql.c_str(), getNewsgroupCallback, ng, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    return *ng;
}

std::vector <NewsGroup> DiskDatabase::get_newsgroups() {
    std::vector <NewsGroup> *ngs = new vector<NewsGroup>;
    char *zErrMsg = 0;
    int rc;
    std::string sql = "SELECT * FROM newsgroups";
    rc = sqlite3_exec(db, sql.c_str(), getNewsgroupsCallback, ngs, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
   return *ngs;
}


