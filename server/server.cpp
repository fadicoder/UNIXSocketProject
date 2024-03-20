#include <iostream>
#include <command.h>


#include <sys/socket.h>
#include <sys/un.h>
#include <iostream>
#include <server.h>
#include <pthread.h>

#define MAX_CONNECTIONS 100
#define VERSION_SIZE 40
#define REJECTION_MESSAGE "REJECTED"
#define VERSION_COMMAND "VERSION"

Command versionCommand = Command("git", 2, "rev-parse", "HEAD");

void* handleClient(Socket* clientSocket) {
    std::cout << "INFO: new client accepted" << std::endl;
    std::string input;
    bool readSuccess;
    do {
        readSuccess = clientSocket->readString(&input);
        if (input == VERSION_COMMAND) {
            versionCommand.execute();
            char version[VERSION_SIZE];
            versionCommand.waitExecution();
            versionCommand.readStdout(version, VERSION_SIZE);
            clientSocket->writeString(version);
        } else {
            clientSocket->writeString(REJECTION_MESSAGE);
        }
    } while(readSuccess);
    std::cout << "INFO: client disconnected" << std::endl;
    delete clientSocket;
    return nullptr;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "ERROR: 1 required argument missing: path to socket" << std::endl;
        return 1;
    }
    signal(SIGPIPE, SIG_IGN); // to make clients disconnect silently
    
    Server server;
    SocketError error;

    error = server.start(argv[1], MAX_CONNECTIONS);
    if (error != SocketError::NO_ERROR) {
        std::cerr << "ERROR: " << getErrorDescription(error) << std::endl;
        return 1;
    }

    std::cout << "INFO: Waiting for a connection..." << std::endl;
    while(true) {
        pthread_t handlerThread;
        Socket* clientSocket = server.acceptClient();
        if (clientSocket) {
            pthread_create(&handlerThread, NULL, (void* (*)(void*)) handleClient, (void*) clientSocket);
        }
    }
}