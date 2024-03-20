#include <iostream>
#include "command.h"


#include <sys/socket.h>
#include <sys/un.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include "mySocket.h"

#define MAX_CONNECTIONS 100
#define VERSION_SIZE 40
#define REJECTION_MESSAGE "REJECTED"

Command versionCommand = Command("git", 2, "rev-parse", "HEAD");

void* handleClient(MySocket* clientSocket) {
    std::string input;
    bool readSuccess;
    do {
        readSuccess = clientSocket->readString(&input);
        std::cout << "Recieved: " << input << std::endl;

        if (input == "VERSION") {
            versionCommand.execute();
            versionCommand.waitExecution();
            char version[VERSION_SIZE];
            versionCommand.readStdout(version, VERSION_SIZE);
            clientSocket->writeString(version);
        } else {
            clientSocket->writeString(REJECTION_MESSAGE);
        }
    } while(readSuccess);
    delete clientSocket;
    return nullptr;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Required argument: path to socket" << std::endl;
        return 1;
    }
    const char* SOCKET_PATH = argv[1];
    
    MySocket mySocket;
    mySocket.create(SOCKET_PATH);

    std::cout << "INFO: Waiting for a connection..." << std::endl;
    while(true) {
        mySocket.acceptClient(handleClient);
    }
}