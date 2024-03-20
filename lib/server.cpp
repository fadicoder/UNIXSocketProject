#include "server.h"

Server::Server(){}

Server::~Server(){
    close(fd);
}

SocketError Server::start(const char* socketPath, const uint maxConnections) {
    sockaddr_un address;
    this->fd = socket(AF_UNIX, SOCK_STREAM, 0);

    if (this->fd == -1) {
        return SocketError::FAILED_SOCKET_CREATION;
    }

    memset(&address, 0, sizeof(sockaddr_un));
    address.sun_family = AF_UNIX;

    if (sizeof(socketPath) > sizeof(address.sun_path) - 1){
        return SocketError::LONG_PATH;
    }

    strncpy(address.sun_path, socketPath, sizeof(address.sun_path) - 1);
    
    if (remove(address.sun_path) == -1 && errno != ENOENT) {
        return SocketError::FAILED_SOCKET_REMOVE;
    }

    if (bind(fd, (sockaddr*) &address, sizeof(sockaddr_un)) == -1) {
        return SocketError::FAILED_BIND;
    }

    if (listen(fd, maxConnections) == -1) {
        return SocketError::FAILED_LISTEN;
    }
    return SocketError::NO_ERROR;
}

Socket* Server::acceptClient() {
    const int cfd = accept(fd, NULL, NULL);
    if (cfd == -1) {
        return nullptr;
    }
    return new Socket(cfd);
}
