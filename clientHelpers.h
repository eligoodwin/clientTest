//
// Created by eli goodwin on 2/5/18.
//

#ifndef CLIENTTEST_CLIENTHELPERS_H
#define CLIENTTEST_CLIENTHELPERS_H
const int BUFFER_SIZE = 500;
#include "ColorDefs.h"
/*
 * prints error message
 * */
void error(const char* msg);

/*
 *gets port from input args
 * */
int getPortFromArgs(char *argv[], int argc);

/*
 * sets username for client
 * */
std::string getUsername();

/* *
 * Sends message to server
 * */
int sendMessage(std::string message, int socketFD);
/*
 * get buffer
 * */
std::string getBuffer(int socketFD);

#endif //CLIENTTEST_CLIENTHELPERS_H
