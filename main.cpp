#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

using namespace std;
int getPortFromArgs(char *argv[], int argc ){
    if(argc != 2){
        return -1;
    }
    return atoi(argv[1]);
}

int main(int argc, char *argv[]) {
    //get the number of arguments should only be 2 : cmd and port number
    cout << "Starting Client..." << endl;
    int port = getPortFromArgs(argv, argc);
    if(port < 5000){
        cout << "Error with port: either port argument was invalid or not provided" << endl;
        return -1;
    }
    cout << "Port number: " << port << endl;
    cout << "Attempting to init cleint..." << endl;

    //init client
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in server_addr;
    char buffer[1024] = {0};
    if((sock - socket(AF_INET, so)))






    char* hello = "hello server! from client";




    return 0;
}