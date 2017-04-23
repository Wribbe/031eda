-- MySQL version.
--
-- We disable foreign key checks temporarily so we can delete the
-- tables in arbitrary order, and so insertion is faster.

PRAGMA foreign_keys = off;

-- Drop the tables if they already exist.

DROP TABLE IF EXISTS newsgroups;
DROP TABLE IF EXISTS articles;

-- Create the tables. The 'check' constraints are not effective in MySQL. 

CREATE TABLE newsgroups (
    id          INTEGER,
    title       TEXT NOT NULL UNIQUE,
    PRIMARY KEY (id)
);

CREATE TABLE articles (
    art_id  INTEGER NOT NULL,
    title   TEXT NOT NULL,
    author  TEXT NOT NULL,
    content TEXT NOT NULL,
    ng_id   INTEGER NOT NULL,
    PRIMARY KEY (art_id),
    FOREIGN KEY (ng_id) REFERENCES newsgroups(id) ON DELETE CASCADE
);

-- We will do a lot of inserts, so we start a transaction to make it faster.
BEGIN TRANSACTION;

INSERT INTO newsgroups (title) VALUES
("Programming"),
("Politics"),
("Movies"),
("Music");

INSERT INTO articles (title, author, content, ng_id) VALUES
("I hate java", "Jonathan", "Python is much better", 1),
("Emacs are for noobs", "Jonathan", "Vim is much better", 1),
("Putin <3 Trump", "Jonathan", "Thanks Obama!", 2);

END TRANSACTION;


-- And re-enable foreign key checks.

PRAGMA foreign_key = on;

