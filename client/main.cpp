
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

    // sockaddr_un addr;
    // char buffer;

    // // Create a new client socket with domain: AF_UNIX, type: SOCK_STREAM, protocol: 0
    // int sfd = socket(AF_UNIX, SOCK_STREAM, 0);

    // if (sfd == -1) {
    //     std::cerr << "ERROR: Failed to create socket" << std::endl;
    // }

    // memset(&addr, 0, sizeof(struct sockaddr_un));
    // addr.sun_family = AF_UNIX;
    // strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);

    // if (connect(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1) {
    //     std::cerr << "ERROR: Failed to connect to server socket. Make sure the server is running" << std::endl;
    //     return 1;
    // }

    MySocket serverSocket;
    if(!serverSocket.init(SOCKET_PATH)){
        return 1;
    }
    std::string input;
    std::string response;
    do {
        std::cin >> input;
        serverSocket.writeString(input);
        serverSocket.readString(&response);
        std::cout << response << std::endl;
    } while(true);

    // Closes our socket; server sees EOF.
    exit(EXIT_SUCCESS);
}