/* myclient.cc: sample client program */
#include "connection.h"
#include "connectionclosedexception.h"
#include "../includes/protocol.h"

#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include <map>

using namespace std;

class protocol_violation: public exception {
 	virtual const char* what() const throw() {
    	return "Client violation of protocol";
 	}
};

/*
 * Read an integer from a server.
 */
int readInt(const Connection& conn) {
	unsigned char byte1 = conn.read();
	unsigned char byte2 = conn.read();
	unsigned char byte3 = conn.read();
	unsigned char byte4 = conn.read();
	return (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
}

int readByte(const Connection& conn) {
	unsigned char byte1 = 0;
	unsigned char byte2 = 0;
	unsigned char byte3 = 0;
	unsigned char byte4 = conn.read();
	return (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
}

/*
 * Read a string from a server given string size
 */
string readString(const Connection& conn, int size){
	stringstream ss;
	for (int i = 0; i != size; ++i) {
		ss << conn.read();
	}
	return ss.str();
}

/*
 * Send an int to a server.
 */
void writeInt(const Connection& conn, int nbr) {
	conn.write((nbr >> 24) & 0xFF);
	conn.write((nbr >> 16) & 0xFF);
	conn.write((nbr >> 8)	 & 0xFF);
	conn.write(nbr & 0xFF);
}

void writeByte(const Connection& conn, int nbr) {
	//conn.write((nbr >> 24) & 0xFF);
	//conn.write((nbr >> 16) & 0xFF);
	//conn.write((nbr >> 8)	 & 0xFF);
	conn.write(nbr & 0xFF);
}

/*
 * Send a string to a server.
 */
void writeString(const Connection& conn, string s) {
	for (char& c : s) {
		conn.write(c);
	}
}



int main(int argc, char* argv[]) {
	if (argc != 3) {
		cout << "Usage: myclient host-name port-number" << endl;
		exit(1);
	}

	int port = -1;
	try {
		port = stoi(argv[2]);
	} catch (exception& e) {
		cout << "Wrong port number. " << e.what() << endl;
		exit(1);
	}

	Connection conn(argv[1], port);
	if (!conn.isConnected()) {
		cout << "Connection attempt failed" << endl;
		exit(1);
	}

	map<string, int> commands;
	commands["help"] = 1;
	commands["list-newsgroups"] = 2;
	commands["create-newsgroup"] = 3;
	commands["delete-newsgroup"] = 4;
	commands["list-articles"] = 5;
	commands["create-article"] = 6;
	commands["delete-article"] = 7;
	commands["get-article"] = 8;


	cout << "Type a command (type 'help' for possible commands): ";
	string s;
	while (cin >> s) {
		try {
			try {
				switch (commands[s]) {
					case 1:				{cout << "Possible commands:\n - 'list-newsgroups'\n - 'create-newsgroup'\n - 'delete-newsgroup'\n - 'list-articles'\n - 'create-article'\n - 'delete-article'\n - 'get-article'" << endl;
														}
														break;

					case 2:	{writeByte(conn, Protocol::COM_LIST_NG);
														writeByte(conn, Protocol::COM_END);

														//Read and list the newsgroups
														if (readByte(conn) != Protocol::ANS_LIST_NG) {throw protocol_violation();}
														if (readByte(conn) != Protocol::PAR_NUM) {throw protocol_violation();}
														int size = readInt(conn);
														cout << "\t[ID, Title]:" << endl;
														stringstream ss;
														for (int i = 0; i < size; ++i) {
															if (readByte(conn) != Protocol::PAR_NUM) {throw protocol_violation();}
															ss << "    -    " <<readInt(conn);
															if (readByte(conn) != Protocol::PAR_STRING) {throw protocol_violation();}
															int stringSize = readInt(conn);
															ss << ", " << readString(conn, stringSize) << endl;
														}
														if (readByte(conn) != Protocol::ANS_END) {throw protocol_violation();}
														cout << ss.str();
														}
														break;

					case 3:	{cout << "Please type a newsgroup name: ";
														string newsgroup;
														cin >> newsgroup;

														//Send command
														writeByte(conn, Protocol::COM_CREATE_NG);
														writeByte(conn, Protocol::PAR_STRING);
														writeInt(conn, newsgroup.size());
														writeString(conn, newsgroup);
														writeByte(conn, Protocol::COM_END);

														//Read reply
														if (readByte(conn) != Protocol::ANS_CREATE_NG) {throw protocol_violation();}
														int answer = readByte(conn);
														if (answer == Protocol::ANS_ACK) {
															cout << "Newsgroup created" << endl;
														} else if (answer == Protocol::ANS_NAK) {
															if (readByte(conn) != Protocol::ERR_NG_ALREADY_EXISTS) {throw protocol_violation();}
															cout << "Newsgroup already exists" << endl;
														} else {throw protocol_violation();}
														if (readByte(conn) != Protocol::ANS_END) {throw protocol_violation();}
														}
														break;

					case 4:	{cout << "Please type a newsgroup ID to delete: ";
														int newsgroupID;
														cin >> newsgroupID;
														if (newsgroupID == 0) {
															cin.clear();
															cin.ignore(10000,'\n');
														}

														//Send command
														writeByte(conn, Protocol::COM_DELETE_NG);
														writeByte(conn, Protocol::PAR_NUM);
														writeInt(conn, newsgroupID);
														writeByte(conn, Protocol::COM_END);

														//Read reply
														if (readByte(conn) != Protocol::ANS_DELETE_NG) {throw protocol_violation();}
														int answer = readByte(conn);
														if (answer == Protocol::ANS_ACK) {
															cout << "Newsgroup deleted" << endl;
														} else if (answer == Protocol::ANS_NAK) {
															if (readByte(conn) != Protocol::ERR_NG_DOES_NOT_EXIST) {throw protocol_violation();}
															cout << "Newsgroup does not exist" << endl;
														} else {throw protocol_violation();}
														if (readByte(conn) != Protocol::ANS_END) {throw protocol_violation();}
														}
														break;

					case 5:		{cout << "Please type a newsgroup ID to list articles from: ";
														int newsgroupID;
														cin >> newsgroupID;
														if (newsgroupID == 0) {
															cin.clear();
															cin.ignore(10000,'\n');
														}

														//Send command
														writeByte(conn, Protocol::COM_LIST_ART);
														writeByte(conn, Protocol::PAR_NUM);
														writeInt(conn, newsgroupID);
														writeByte(conn, Protocol::COM_END);

														//Read reply
														if (readByte(conn) != Protocol::ANS_LIST_ART) {throw protocol_violation();}
														int answer = readByte(conn);
														if (answer == Protocol::ANS_ACK) {
															if (readByte(conn) != Protocol::PAR_NUM) {throw protocol_violation();}
															int size = readInt(conn);
															stringstream ss;
															for (int i = 0; i < size; ++i) {
																if (readByte(conn) != Protocol::PAR_NUM) {throw protocol_violation();}
																	ss << "Article ID: " << readInt(conn);
																	if (readByte(conn) != Protocol::PAR_STRING) {throw protocol_violation();}
																	int stringSize = readInt(conn);
																	ss << ", " << readString(conn, stringSize);
																}
																cout << ss.str() << endl;
															} else if (answer == Protocol::ANS_NAK) {
																if (readByte(conn) != Protocol::ERR_NG_DOES_NOT_EXIST) {throw protocol_violation();}
																cout << "Newsgroup does not exist" << endl;
															} else {throw protocol_violation();}
															if (readByte(conn) != Protocol::ANS_END) {throw protocol_violation();}
														}
														break;

					case 6:	{cout << "Please type a newsgroup ID to create the article in: ";
														int newsgroupID;
														cin >> newsgroupID;
														if (newsgroupID == 0) {
															cin.clear();
															cin.ignore(10000,'\n');
														}

														cout << "Please type the article title: ";
														string title;
														cin >> title;

														cout << "Please type the article author: ";
														string author;
														cin >> author;

														cout << "Please type the article text: ";
														string text;
														cin >> text;

														//Send article
														writeByte(conn, Protocol::COM_CREATE_ART);
														writeByte(conn, Protocol::PAR_NUM);
														writeInt(conn, newsgroupID);
														writeByte(conn, Protocol::PAR_STRING);
														writeInt(conn, title.size());
														writeString(conn, title);
														writeByte(conn, Protocol::PAR_STRING);
														writeInt(conn, author.size());
														writeString(conn, author);
														writeByte(conn, Protocol::PAR_STRING);
														writeInt(conn, text.size());
														writeString(conn, text);
														writeByte(conn, Protocol::COM_END);

														//Read reply
														if (readByte(conn) != Protocol::ANS_CREATE_ART) {throw protocol_violation();}
														int answer = readByte(conn);
														if (answer == Protocol::ANS_ACK) {
															cout << "Article created" << endl;
														} else if (answer == Protocol::ANS_NAK) {
															if (readByte(conn) != Protocol::ERR_NG_DOES_NOT_EXIST) {throw protocol_violation();}
															cout << "Newsgroup does not exist" << endl;
														} else {throw protocol_violation();}
														if (readByte(conn) != Protocol::ANS_END) {throw protocol_violation();}
														}
														break;

					case 7:	{cout << "Please type a newsgroup ID delete an article from: ";
														int newsgroupID;
														cin >> newsgroupID;
														if (newsgroupID == 0) {
															cin.clear();
															cin.ignore(10000,'\n');
														}

														cout << "Please type the article ID to delete: ";
														int articleID;
														cin >> articleID;
														if (articleID == 0) {
															cin.clear();
															cin.ignore(10000,'\n');
														}

														//Send command
														writeByte(conn, Protocol::COM_DELETE_ART);
														writeByte(conn, Protocol::PAR_NUM);
														writeInt(conn, newsgroupID);
														writeByte(conn, Protocol::PAR_NUM);
														writeInt(conn, articleID);
														writeByte(conn, Protocol::COM_END);

														//Read reply
														if (readByte(conn) != Protocol::ANS_DELETE_ART) {throw protocol_violation();}
														int answer = readByte(conn);
														if (answer == Protocol::ANS_ACK) {
															cout << "Article deleted" << endl;
														} else if (answer == Protocol::ANS_NAK) {
															int answer2 = readByte(conn);
															if (answer2 == Protocol::ERR_NG_DOES_NOT_EXIST) {
																cout << "Newsgroup does not exist" << endl;
															} else if (answer2 == Protocol::ERR_ART_DOES_NOT_EXIST){
																cout << "Article does not exist" << endl;
															}else{throw protocol_violation();}
														} else {throw protocol_violation();}
														if (readByte(conn) != Protocol::ANS_END) {throw protocol_violation();}
														}
														break;

					case 8:		{cout << "Please type a newsgroup ID get an article from: ";
														int newsgroupID;
														cin >> newsgroupID;
														if (newsgroupID == 0) {
															cin.clear();
															cin.ignore(10000,'\n');
														}

														cout << "Please type the article ID: ";
														int articleID;
														cin >> articleID;
														if (articleID == 0) {
															cin.clear();
															cin.ignore(10000,'\n');
														}

														//Send command
														writeByte(conn, Protocol::COM_GET_ART);
														writeByte(conn, Protocol::PAR_NUM);
														writeInt(conn, newsgroupID);
														writeByte(conn, Protocol::PAR_NUM);
														writeInt(conn, articleID);
														writeByte(conn, Protocol::COM_END);

														//Read reply
														if (readByte(conn) != Protocol::ANS_GET_ART) {throw protocol_violation();}
														int answer = readByte(conn);
														if (answer == Protocol::ANS_ACK) {
															if (readByte(conn) != Protocol::PAR_STRING) {throw protocol_violation();}
															int size = readInt(conn);
															string title = readString(conn, size);
															if (readByte(conn) != Protocol::PAR_STRING) {throw protocol_violation();}
															size = readInt(conn);
															string author = readString(conn, size);
															if (readByte(conn) != Protocol::PAR_STRING) {throw protocol_violation();}
															size = readInt(conn);
															string text = readString(conn, size);
															cout << "Title: " << title << "\nAuthor: " << author << "\nText: " << text << endl;
														} else if (answer == Protocol::ANS_NAK) {
															int answer2 = readByte(conn);
															if (answer2 == Protocol::ERR_NG_DOES_NOT_EXIST) {
																cout << "Newsgroup does not exist" << endl;
															} else if (answer2 == Protocol::ERR_ART_DOES_NOT_EXIST){
																cout << "Article does not exist" << endl;
															}else{throw protocol_violation();}
														} else {throw protocol_violation();}
														if (readByte(conn) != Protocol::ANS_END) {throw protocol_violation();}
														}
														break;
				}
			} catch (protocol_violation& e){
				cout << "Client violation of protocol" << endl;
			}
			cout << "Type another command: ";
		} catch (ConnectionClosedException&) {
			cout << " no reply from server. Exiting." << endl;
			exit(1);
		}
	}
}
