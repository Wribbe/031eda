/* myserver.cc: sample server program */
#include "server.h"
#include "connection.h"
#include "connectionclosedexception.h"
#include "../includes/databaseinterface.h"
#include "../includes/memorydatabase.h"
#include "../includes/diskdatabase.h"
#include "../includes/protocol.h"

#include <memory>
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>

using namespace std;

class protocol_violation: public exception {
 	virtual const char* what() const throw() {
    	return "Client violation of protocol";
 	}
};

/*
 * Read an integer from a client.
 * Return: Integer value.
 */
int readInt(const shared_ptr<Connection>& conn) {
	unsigned char byte1 = conn->read();
	unsigned char byte2 = conn->read();
	unsigned char byte3 = conn->read();
	unsigned char byte4 = conn->read();
	return (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
}

/*
 * Read a byte from a client.
 * Return: Integer convertion of byte value.
 */
int readByte(const shared_ptr<Connection>& conn) {
	unsigned char byte = conn->read();
	return (0 << 24) | (0 << 16) | (0 << 8) | byte;
}

/*
 * Read a string from a client given string size
 * Return: String from client.
 */
string readString(const shared_ptr<Connection>& conn, int size){
	stringstream ss;
	for (int i = 0; i != size; ++i) {
		ss << conn->read();
	}
	return ss.str();
}

/*
 * Send an int to a client.
 */
void writeInt(const shared_ptr<Connection>& conn, int nbr) {
	conn->write((nbr >> 24) & 0xFF);
	conn->write((nbr >> 16) & 0xFF);
	conn->write((nbr >> 8)	 & 0xFF);
	conn->write(nbr & 0xFF);
}

/*
 * Send a byte to a client.
 */
void writeByte(const shared_ptr<Connection>& conn, int nbr) {
	conn->write(nbr & 0xFF);
}

/*
 * Send a string to a client.
 */
void writeString(const shared_ptr<Connection>& conn, string s) {
	for (char& c : s) {
		conn->write(c);
	}
}

/*
 *Read command 'list-newsgroups' from client and sends back the list of newsgroups to client.
 *Protocol format:
 *  Client: COM_LIST_NG, COM_END
 *  Server: ANS_LIST_NG, PAR_NUM, N, [PAR_NUM, N, PAR_STRING, N, char1...charN]*, ANS_END
 */
void list_newsgroups(const shared_ptr<Connection>& conn, DatabaseInterface* database) {
    if (readByte(conn) != Protocol::COM_END) {throw protocol_violation();}

    //Send answer
    writeByte(conn, Protocol::ANS_LIST_NG);
    //Send size of newsgroup list
    writeByte(conn, Protocol::PAR_NUM);
    writeInt(conn, database->get_newsgroups().size());
    //Send id and title of each newsgroup
    for (auto &newsgroup : database->get_newsgroups()){
        writeByte(conn, Protocol::PAR_NUM);
        writeInt(conn, newsgroup.id());
        writeByte(conn, Protocol::PAR_STRING);
        writeInt(conn, newsgroup.title().size());
        writeString(conn, newsgroup.title());
    }
    writeByte(conn, Protocol::ANS_END);
}

/*
 *Read command 'create-newsgroup' from client and sends back ack or nak to client.
 *Protocol format:
 *  Client: COM_CREATE_NG, PAR_STRING, N, char1...charN, COM_END
 *  Server: ANS_CREATE_NG, [ANS_ACK | ANS_NAK, ERR_NG_ALREADY_EXISTS], ANS_END
 */
void create_newsgroup(const shared_ptr<Connection>& conn, DatabaseInterface* database) {
    if (readByte(conn) != Protocol::PAR_STRING) {throw protocol_violation();}
    //Read newsgroup name
    int size = readInt(conn);
    string newsgroup = readString(conn, size);
    if (readByte(conn) != Protocol::COM_END) {throw protocol_violation();}

    //Send answer
    writeByte(conn, Protocol::ANS_CREATE_NG);
    //Create newgroup in database
    if(database->create_newsgroup(newsgroup)){
        writeByte(conn, Protocol::ANS_ACK);
    } else {
        cout << "Newsgroup already exists" << endl;
        writeByte(conn, Protocol::ANS_NAK);
        writeByte(conn, Protocol::ERR_NG_ALREADY_EXISTS);
    }
    writeByte(conn, Protocol::ANS_END);
}

/*
 *Read command 'delete-newsgroup' from client and sends back ack or nak to client.
 *Protocol format:
 *  Client: COM_DELETE_NG, PAR_NUM, N, COM_END
 *  Server: ANS_DELETE_NG, [ANS_ACK | ANS_NAK, ERR_NG_DOES_NOT_EXISTS], ANS_END
 */
void delete_newsgroup(const shared_ptr<Connection>& conn, DatabaseInterface* database){
    if (readByte(conn) != Protocol::PAR_NUM) {throw protocol_violation();}
    int newsgroupID = readInt(conn);
    if (readByte(conn) != Protocol::COM_END) {throw protocol_violation();}

    //Send answer
    writeByte(conn, Protocol::ANS_DELETE_NG);
    //Delete newsgroup in database with newsgroupID
    if(database->exists(newsgroupID)){
        database->delete_newsgroup(newsgroupID);
        writeByte(conn, Protocol::ANS_ACK);
    } else {
        cout << "Newsgroup does not exist" << endl;
        writeByte(conn, Protocol::ANS_NAK);
        writeByte(conn, Protocol::ERR_NG_DOES_NOT_EXIST);
    }
    writeByte(conn, Protocol::ANS_END);
}

/*
 *Read command 'list-articles' from client and sends back the list of articles to client.
 *Protocol format:
 *  Client: COM_LIST_ART, PAR_NUM, N, COM_END
 *  Server: ANS_LIST_ART, [ANS_ACK, PAR_NUM, N, [PAR_NUM, N, PAR_STRING, N, char1...charN,]* | ANS_NAK, ERR_NG_DOES_NOT_EXIST], ANS_END
 */
void list_articles(const shared_ptr<Connection>& conn, DatabaseInterface* database){
    if (readByte(conn) != Protocol::PAR_NUM) {throw protocol_violation();}
    int newsgroupID = readInt(conn);
    if (readByte(conn) != Protocol::COM_END) {throw protocol_violation();}

    //Send answer
    writeByte(conn, Protocol::ANS_LIST_ART);
    //List articles in database under newsgroupID
    if (database->exists(newsgroupID)){
        vector<Article>& articles = database->get_newsgroup(newsgroupID).get_articles();
        writeByte(conn, Protocol::ANS_ACK);
        writeByte(conn, Protocol::PAR_NUM);
        writeInt(conn, articles.size());
        for (auto &article : articles){
            writeByte(conn, Protocol::PAR_NUM);
            writeInt(conn, article.id());
            writeByte(conn, Protocol::PAR_STRING);
            writeInt(conn, article.title().size());
            writeString(conn, article.title());
        }
    } else {
        cout << "Newsgroup does not exist" << endl;
        writeByte(conn, Protocol::ANS_NAK);
        writeByte(conn, Protocol::ERR_NG_DOES_NOT_EXIST);
    }
    writeByte(conn, Protocol::ANS_END);
}

/*
 *Read command 'create-article' from client and sends back ack or nak to client.
 *Protocol format:
 *  Client: COM_CREATE_ART, PAR_NUM, N, PAR_STRING, N, char1...charN, PAR_STRING, N, char1...charN, PAR_STRING, N, char1...charN, COM_END
 *  Server: ANS_CREATE_ART, [ANS_ACK | ANS_NAK, ERR_NG_DOES_NOT_EXISTS], ANS_END
 */
void create_article(const shared_ptr<Connection>& conn, DatabaseInterface* database){
    if (readByte(conn) != Protocol::PAR_NUM) {throw protocol_violation();}
    int newsgroupID = readInt(conn);
    if (readByte(conn) != Protocol::PAR_STRING) {throw protocol_violation();}
    int size = readInt(conn);
    string title = readString(conn, size);
    if (readByte(conn) != Protocol::PAR_STRING) {throw protocol_violation();}
    size = readInt(conn);
    string author = readString(conn, size);
    if (readByte(conn) != Protocol::PAR_STRING) {throw protocol_violation();}
    size = readInt(conn);
    string text = readString(conn, size);
    if (readByte(conn) != Protocol::COM_END) {throw protocol_violation();}

    //Send answer
    writeByte(conn, Protocol::ANS_CREATE_ART);
    //Create article in database with newsgroupID, title, author, text
    if (database->exists(newsgroupID)){
        database->save_article(newsgroupID, title, author, text);
        writeByte(conn, Protocol::ANS_ACK);
    } else {
        cout << "Newsgroup does not exist" << endl;
        writeByte(conn, Protocol::ANS_NAK);
        writeByte(conn, Protocol::ERR_NG_DOES_NOT_EXIST);
    }
    writeByte(conn, Protocol::ANS_END);
}

/*
 *Read command 'delete-article' from client and sends back ack or nak to client.
 *Protocol format:
 *  Client: COM_DELETE_ART, PAR_NUM, N, PAR_NUM, N, COM_END
 *  Server: ANS_DELETE_ART, [ANS_ACK | ANS_NAK, [ERR_NG_DOES_NOT_EXIST | ERR_ART_DOES_NOT_EXIST]], ANS_END
 */
void delete_article(const shared_ptr<Connection>& conn, DatabaseInterface* database){
    if (readByte(conn) != Protocol::PAR_NUM) {throw protocol_violation();}
    int newsgroupID = readInt(conn);
    if (readByte(conn) != Protocol::PAR_NUM) {throw protocol_violation();}
    int articleID = readInt(conn);
    if (readByte(conn) != Protocol::COM_END) {throw protocol_violation();}

    //Send answer
    writeByte(conn, Protocol::ANS_DELETE_ART);
    //Delete article in database with newsgroupID, articleID
    if (database->exists(newsgroupID)) {
        if (database->get_newsgroup(newsgroupID).article_exists(articleID)) {
            database->delete_article(newsgroupID, articleID);
            writeByte(conn, Protocol::ANS_ACK);
        } else {
            cout << "Article does not exist" << endl;
            writeByte(conn, Protocol::ANS_NAK);
            writeByte(conn, Protocol::ERR_ART_DOES_NOT_EXIST);
        }
    } else {
        cout << "Newsgroup does not exist" << endl;
        writeByte(conn, Protocol::ANS_NAK);
        writeByte(conn, Protocol::ERR_NG_DOES_NOT_EXIST);
    }
    writeByte(conn, Protocol::ANS_END);
}

/*
 *Read command 'get-article' from client and sends back article title, author and text.
 *Protocol format:
 *  Client: COM_GET_ART, PAR_NUM, N, PAR_NUM, N, COM_END
 *  Server: ANS_GET_ART, [ANS_ACK, PAR_STRING, N, char1...charN, PAR_STRING, N, char1...charN, PAR_STRING, N, char1...charN | ANS_NAK, [ERR_NG_DOES_NOT_EXIST | ERR_ART_DOES_NOT_EXIST]], ANS_END
 */
void get_article(const shared_ptr<Connection>& conn, DatabaseInterface* database){
    if (readByte(conn) != Protocol::PAR_NUM) {throw protocol_violation();}
    int newsgroupID = readInt(conn);
    if (readByte(conn) != Protocol::PAR_NUM) {throw protocol_violation();}
    int articleID = readInt(conn);
    if (readByte(conn) != Protocol::COM_END) {throw protocol_violation();}

    //Send answer
    writeByte(conn, Protocol::ANS_GET_ART);
    //Create article in database with newsgroupID, title, author, text
    if (database->exists(newsgroupID)) {
        if (database->get_newsgroup(newsgroupID).article_exists(articleID)) {
            Article& article = database->load_article(newsgroupID, articleID);
            writeByte(conn, Protocol::ANS_ACK);
            writeByte(conn, Protocol::PAR_STRING);
            writeInt(conn, article.title().size());
            writeString(conn, article.title());
            writeByte(conn, Protocol::PAR_STRING);
            writeInt(conn, article.author().size());
            writeString(conn, article.author());
            writeByte(conn, Protocol::PAR_STRING);
            writeInt(conn, article.text().size());
            writeString(conn, article.text());
        } else {
            cout << "Article does not exist" << endl;
            writeByte(conn, Protocol::ANS_NAK);
            writeByte(conn, Protocol::ERR_ART_DOES_NOT_EXIST);
        }
    } else {
        cout << "Newsgroup does not exist" << endl;
        writeByte(conn, Protocol::ANS_NAK);
        writeByte(conn, Protocol::ERR_NG_DOES_NOT_EXIST);
    }
    writeByte(conn, Protocol::ANS_END);
}

void readCommands(const shared_ptr<Connection>& conn, DatabaseInterface* database) {
	try {
		//Read the first command
		int command = readByte(conn);
		//Create Article
		switch (command) {
			//List newsgroups
			case Protocol::COM_LIST_NG:     list_newsgroups(conn, database);
											break;
			//Create newsgroup
			case Protocol::COM_CREATE_NG:   create_newsgroup(conn, database);
											break;
			//Delete newsgroupID
			case Protocol::COM_DELETE_NG:	delete_newsgroup(conn, database);
											break;
			//List articles in newsgroupID
			case Protocol::COM_LIST_ART:	list_articles(conn, database);
											break;
			//Create article with name
			case Protocol::COM_CREATE_ART:	create_article(conn, database);
											break;
			//Delete article with ID
			case Protocol::COM_DELETE_ART:	delete_article(conn, database);
											break;
			//Get article with ID
			case Protocol::COM_GET_ART:		get_article(conn, database);
											break;
			default:	throw protocol_violation();
						break;
		}
	} catch (exception& e) {
		cout << e.what() << endl;
	}
}

int main(int argc, char* argv[]){
	if (argc != 3) {
		cout << "Usage: ./myserver port-number database-type" << endl;
		exit(1);
	}

	int port = -1;
	try {
		port = stoi(argv[1]);
	} catch (exception& e) {
		cout << "Wrong port number. " << e.what() << endl;
		exit(1);
	}

	string database_type;
	try {
		database_type = argv[2];
		if (database_type != "memory" && database_type != "disk") {
	        throw invalid_argument( "received negative value" );
		}
	} catch (exception& e) {
		cout << "Please provide a database-type: 'memory' or 'disk'" << endl;
		exit(1);
	}

	Server server(port);
	if (!server.isReady()) {
		cout << "Server initialization error." << endl;
		exit(1);
	}

	DatabaseInterface* database;
	if (database_type == "memory") {
		database = new MemoryDatabase();
	} else if (database_type == "disk") {
		//database = new DiskDatabase();
	}

	cout << "Server running... waiting for connection" << endl;


	while (true) {
		auto conn = server.waitForActivity();
		if (conn != nullptr) {
			try {
				readCommands(conn, database);
			} catch (ConnectionClosedException&) {
				server.deregisterConnection(conn);
				cout << "Client closed connection" << endl;
			}
		} else {
			conn = make_shared<Connection>();
			server.registerConnection(conn);
			cout << "New client connects" << endl;
		}
	}
}
