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
#include <thread>


using namespace std;
bool listening = true;

void makeServer(char address[], int port);

int main(int argc, char *argv[]) {
    //get the number of arguments should only be 2 : cmd and port number
    int port = getPortFromArgs(argv, argc);
    if(port < 5000){
        error(RED "Error with port: either port argument was invalid or not provided" RESET);
    }
    cout << YELLOW << "Welcome to the client program. If you wish to quit while chatting with the server enter: '/quit' into the terminal" << RESET <<endl;
    string username = getUsername();
    cout << YELLOW << "...Attempting to init client..." << endl;
    cout  << "\tPort number: " << port << endl;
    cout << "\tTarget host: " << argv[1] << RESET << endl;

    //prepare the connection
    struct sockaddr_in serverAddress;
    struct hostent* serverHostInfo;
    memset((char*)&serverAddress, '\0', sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverHostInfo = gethostbyname(argv[1]);
    if(!serverHostInfo){
        error(RED "ERROR: host could not be determined" RESET);
    }
    memcpy((char*)&serverAddress.sin_addr.s_addr,
           (char*)serverHostInfo->h_addr,
           serverHostInfo->h_length);

    //init socket
    cout << YELLOW << "\tPreparing the socket" << RESET << endl;
    int socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if(socketFD < 0){
        error(RED"ERROR: socket could not be made. Exiting"RESET);
    }
    if(connect(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0){
        error(RED"ERROR: Client could not connect to server"RESET);
    }
    else{
        cout << GREEN << "****CONNECTED****" << RESET << endl;
    }
    cout << YELLOW << "...Creating listener" << RESET << endl;
    thread listenerThread(makeServer, serverHostInfo, port);

    //begin chat
    bool connected = true;
    while(connected){
        string stringInput = "";
        cout << GREEN << "TO: " << RESET;
        getline(cin, stringInput);
        if(stringInput != "/quit"){
            stringInput.insert(0, "> ");
            stringInput.insert(0, username);
            sendMessage(stringInput, socketFD);
            //reset the buffer
            char buffer[BUFFER_SIZE];
            memset(buffer, '\0', BUFFER_SIZE * sizeof(char));
            read(socketFD, buffer, BUFFER_SIZE);

            if(strcmp(buffer, "Server is terminating connection") == 0){
                cout << CYAN  <<"Server is shutting down" << RESET <<endl;
                cout << RED << "****DISCONNECTED****" << RESET << endl;
                connected = false;
            }
            else{
                cout << MAGENTA<< "FROM: " << buffer << RESET << endl;
            }
        }
        else{
            sendMessage("CLIENT IS QUITTING", socketFD);
            connected = false;
            listening = false;
        }
    }

    close(socketFD);
    cout << YELLOW << "Program exiting" << RESET<< endl;
    return 0;
}

void makeServer(char address[], int port){
    int listenSocketFD, establishedConnectionFD, portNumber;
    socklen_t  sizeOfClientINfo;
    char* received = "RECEIVED";
    struct sockaddr_in serverAddress, clientAddress;
    memset((char*)&serverAddress, '\0',  sizeof(serverAddress));
    portNumber = port;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(portNumber);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    listenSocketFD = socket(AF_INET, SOCK_STREAM, 0);
    if(listenSocketFD < 0)
        error("ERROR on accept");

    char buffer[500];

    while(listening){
        memset(buffer, '\0', 500 * sizeof(char));
        int incoming  = recv(establishedConnectionFD, buffer, 500, 0);
        if(incoming < 0)
            error("ERROR: socket is screwy");
        cout << buffer << endl;
        send(establishedConnectionFD, received, strlen(received), 0);
        close(establishedConnectionFD);
    }
    close(listenSocketFD);
}