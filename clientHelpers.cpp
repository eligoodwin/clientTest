//
// Created by eli goodwin on 2/5/18.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include "clientHelpers.h"

using namespace std;

void error(const char* msg){
    perror(msg);
    exit(0);
}

int getPortFromArgs(char *argv[], int argc ){
    if(argc != 3){
        return -1;
    }
    return atoi(argv[2]);
}


string getUsername(){
    string username = "";
    string response = "";
    cout << GREEN <<"Enter a username: " << RESET;
    do{
        getline(cin, username);
        if(username.size() > 10){
            cout << RED << "Please specify a username less than 10 characters long: " << RESET;
        }
        else{
            cout << GREEN << "You selected: " << username << " do you wish to keep (yes/no)?" << RESET;
            getline(cin, response);
            if(response != "yes"){
                cout << YELLOW << "please select a new username: " << RESET;
            }
        }
    }while(username.size() > 10 || response != "yes");
    return username;
}


int sendMessage(string message, int socketFD){
    char messageToSend[BUFFER_SIZE];
    memset(messageToSend, '\0', BUFFER_SIZE* sizeof(char));
    strcpy(messageToSend, message.c_str());
    return send(socketFD, messageToSend, strlen(messageToSend), 0);
}

string getBuffer(int socketFD){
    char buffer[BUFFER_SIZE];
    memset(buffer, '\0', BUFFER_SIZE * sizeof(char));
    read(socketFD, buffer, BUFFER_SIZE);
    string returnString(buffer);
    return returnString;
}