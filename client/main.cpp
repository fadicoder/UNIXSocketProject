
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

void sendCommandArgs(Socket socket, int argc, char** argv) {
    std::string response;
    for (int i = 2; i < argc; i++){
        socket.writeString(argv[i]);
        socket.readString(&response);
        std::cout << response << std::endl;
    }
}

void runShell(Socket socket) {
    std::string input;
    std::string response;
    std::cout << "Welcome to UNIX socket shell! You can enter a command for the server or press CTRL+C to exit" << std::endl;
    while (true) {
        std::cout << SHELL_LINE_START;
        std::cin >> input;
        socket.writeString(input);
        socket.readString(&response);
        std::cout << response << std::endl;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "ERROR: 1 required argument: path to socket" << std::endl;
        return 1;
    }

    signal(SIGPIPE, sigpipeHandler);

    Socket socket;
    SocketError error;

    error = socket.connectToServer(argv[1]);
    if (error != SocketError::NO_ERROR) {
        std::cerr << "ERROR: " << getErrorDescription(error) << std::endl;
        return 1;
    }
    
    if (argc > 2) {
        sendCommandArgs(socket, argc, argv);
        return 0;
    }

    runShell(socket);
}