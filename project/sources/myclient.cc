/* myclient.cc: sample client program */
#include "connection.h"
#include "connectionclosedexception.h"

#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include "protocol.h"

using namespace std;

unsigned int readCommand() {
    for (int code = Protocol::COM_LIST_NG; code != Protocol::COM_END; ++code) {
        std::cout << code << ": " << codeToString(code) << std::endl;
    }
    unsigned int command;
    do {
        std::cout << "Enter command: ";
        std::cin >> command;
    } while (!(command >= Protocol::COM_LIST_NG && command <= Protocol::COM_GET_ART));
    return command;
}

/*
 * Send an integer to the server as four bytes.
 */
void writeNumber(const Connection &conn, int value) {
    conn.write((value >> 24) & 0xFF);
    conn.write((value >> 16) & 0xFF);
    conn.write((value >> 8) & 0xFF);
    conn.write(value & 0xFF);
}

/*
 * Read a string from the server.
 */
string readString(const Connection &conn) {
    string s;
    char ch;
    while ((ch = conn.read()) != '$') {
        s += ch;
    }
    return s;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Usage: myclient host-name port-number" << endl;
        exit(1);
    }

    int port = -1;
    try {
        port = stoi(argv[2]);
    } catch (exception &e) {
        cerr << "Wrong port number. " << e.what() << endl;
        exit(1);
    }

    Connection conn(argv[1], port);
    if (!conn.isConnected()) {
        cerr << "Connection attempt failed" << endl;
        exit(1);
    }

    while (true) {
        try {
            //TODO
            //Refactor duplicate code into methods in procotol.cc
            unsigned int command = readCommand();
            switch (command) {
                case Protocol::COM_LIST_NG: { //Must use compound stmt when we have a declaration stmt
                    conn.write(Protocol::COM_LIST_NG);
                    conn.write(Protocol::COM_END);
                    unsigned char data = conn.read();
                    break;
                }
                case Protocol::COM_CREATE_NG: {
                    conn.write(Protocol::COM_CREATE_NG);
                    //conn.write(name of ng);
                    conn.write(Protocol::COM_END);
                    unsigned char data = conn.read();
                    break;
                }
                case Protocol::COM_DELETE_NG: {
                    conn.write(Protocol::COM_DELETE_NG);
                    //conn.write(some parameters);
                    conn.write(Protocol::COM_END);
                    unsigned char data = conn.read();
                    break;
                }
                case Protocol::COM_LIST_ART: {
                    conn.write(Protocol::COM_LIST_ART);
                    //conn.write(some parameters);
                    conn.write(Protocol::COM_END);
                    unsigned char data = conn.read();
                    break;
                }
                case Protocol::COM_CREATE_ART: {
                    conn.write(Protocol::COM_CREATE_ART);
                    //conn.write(some parameters);
                    conn.write(Protocol::COM_END);
                    unsigned char data = conn.read();
                    break;
                }
                case Protocol::COM_DELETE_ART: {
                    conn.write(Protocol::COM_DELETE_ART);
                    //conn.write(some parameters);
                    conn.write(Protocol::COM_END);
                    unsigned char data = conn.read();
                    break;
                }
                case Protocol::COM_GET_ART: {
                    conn.write(Protocol::COM_GET_ART);
                    conn.write(Protocol::COM_END);
                    unsigned char data = conn.read();
                    break;
                }
                default:
                    break;
            }
        } catch (ConnectionClosedException &) {
            cout << " no reply from server. Exiting." << endl;
            exit(1);
        }
    }
}

