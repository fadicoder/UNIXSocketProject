
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <iostream>
#include <signal.h>
#include <socket.h>

#define SHELL_LINE_START ">>> "

void sigpipeHandler(int signum) {
    std::cerr << "ERROR: Server disconnected" << std::endl;
    exit(1);
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Required argument: path to socket" << std::endl;
        return 1;
    }
    const char* SOCKET_PATH = argv[1];

    signal(SIGPIPE, sigpipeHandler);

    Socket socket;
    if(!socket.initialize(SOCKET_PATH)){
        return 1;
    }
    if (!socket.connectToServer()){
        return 1;
    }

    std::string response;
    
    if (argc > 2){
        for (uint i = 2; i < argc; i++){
            socket.writeString(argv[i]);
            socket.readString(&response);
            std::cout << response << std::endl;
        }
        return 0;
    }
    std::string input;
    do {
        std::cout << SHELL_LINE_START;
        std::cin >> input;
        socket.writeString(input);
        socket.readString(&response);
        std::cout << response << std::endl;
    } while(true);
}