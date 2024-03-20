
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <iostream>
#include "mySocket.h"
int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Required argument: path to socket" << std::endl;
        return 1;
    }
    const char* SOCKET_PATH = argv[1];

    MySocket serverSocket;
    if(!serverSocket.init(SOCKET_PATH)){
        return 1;
    }
    std::string response;
    
    if (argc > 2){
        for (uint i = 2; i < argc; i++){
            serverSocket.writeString(argv[i]);
            serverSocket.readString(&response);
            std::cout << response << std::endl;
        }
        return 0;
    }
    std::string input;
    do {
        std::cout << ">>> ";
        std::cin >> input;
        serverSocket.writeString(input);
        serverSocket.readString(&response);
        std::cout << response << std::endl;
    } while(true);

    // Closes our socket; server sees EOF.
    exit(EXIT_SUCCESS);
}