//
// Created by Jonathan Schurmann on 3/30/17.
//

#include "protocol.h"

std::string codeToString(const unsigned int &code) {
    switch (code) {
        case Protocol::COM_LIST_NG:
            return "COM_LIST_NG";
        case Protocol::COM_CREATE_NG:
            return "COM_CREATE_NG";
        case Protocol::COM_DELETE_NG:
            return "COM_DELETE_NG";
        case Protocol::COM_LIST_ART:
            return "COM_LIST_ART";
        case Protocol::COM_CREATE_ART:
            return "COM_CREATE_ART";
        case Protocol::COM_DELETE_ART:
            return "COM_DELETE_ART";
        case Protocol::COM_GET_ART:
            return "COM_GET_ART";
        case Protocol::COM_END:
            return "COM_END";
        case Protocol::ANS_LIST_NG:
            return "ANS_LIST_NG";
        case Protocol::ANS_CREATE_NG:
            return "ANS_CREATE_NG";
        case Protocol::ANS_DELETE_NG:
            return "ANS_DELETE_NG";
        case Protocol::ANS_LIST_ART:
            return "ANS_LIST_ART";
        case Protocol::ANS_CREATE_ART:
            return "ANS_CREATE_ART";
        case Protocol::ANS_DELETE_ART:
            return "ANS_DELETE_ART";
        case Protocol::ANS_GET_ART:
            return "ANS_GET_ART";
        case Protocol::ANS_END:
            return "ANS_END";
        case Protocol::ANS_ACK:
            return "ANS_ACK";
        case Protocol::ANS_NAK:
            return "ANS_NAK";
        case Protocol::PAR_STRING:
            return "PAR_STRING";
        case Protocol::PAR_NUM:
            return "PAR_NUM";
        case Protocol::ERR_NG_ALREADY_EXISTS:
            return "ERR_NG_ALREADY_EXISTS";
        case Protocol::ERR_NG_DOES_NOT_EXIST:
            return "ERR_NG_DOES_NOT_EXIST";
        case Protocol::ERR_ART_DOES_NOT_EXIST:
            return "ERR_ART_DOES_NOT_EXIST";
        case Protocol::ERR_UNSPECIFIED:
            return "ERR_UNSPECIFIED";
        default:
            return "";
    }
}

