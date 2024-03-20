#include "socket.h"

Socket::Socket() {}

Socket::Socket(int fd) {
    this->fd = fd;
}

Socket::~Socket() {
    close(fd);
}

SocketError Socket::connectToServer(const char* socketPath) {
    sockaddr_un address;

    this->fd = socket(AF_UNIX, SOCK_STREAM, 0);

    if (this->fd == -1) {
        return SocketError::FAILED_SOCKET_CREATION;
    }

    memset(&address, 0, sizeof(sockaddr_un));
    address.sun_family = AF_UNIX;
    strncpy(address.sun_path, socketPath, sizeof(address.sun_path) - 1);

    if (connect(this->fd, (sockaddr*) &address, sizeof(sockaddr_un)) == -1) {
        return SocketError::FAILED_CONNECTION;
    }
    return SocketError::NO_ERROR;
}

bool Socket::writeData(void* data, ssize_t size) {
    ssize_t nbBytesSent = size;
    ssize_t nbBytesLeft = size;
    while (nbBytesLeft > 0) {
        nbBytesSent = write(fd, data, size);
        nbBytesLeft = size - nbBytesSent;
        if (nbBytesSent <= 0) {
            return false;
        }
    }
    return true;
}

bool Socket::writeInt(int value) {
    return this->writeData(&value, sizeof(int));
}

bool Socket::writeFloat(float value) {
    return this->writeData(&value, sizeof(float));
}

bool Socket::writeChar(char value) {
    return this->writeData(&value, sizeof(char));
}

bool Socket::writeString(std::string value) {
    if (!this->writeInt(value.size())){
        return false;
    }
    if (!this->writeData((void*) value.c_str(), value.size() * sizeof(char))){
        return false;
    }
    return true;
}

bool Socket::readData(void* data, ssize_t size) {
    ssize_t nbBytesread = size;
    ssize_t nbBytesLeft = size;
    while (nbBytesLeft > 0) {
        nbBytesread = read(this->fd, data, size);
        nbBytesLeft = size - nbBytesread;
        if (nbBytesread <= 0) {
            return false;
        }
    }
    return true;
}

bool Socket::readInt(int* value) {
    return this->readData(value, sizeof(int));
}

bool Socket::readFloat(float* value) {
    return this->readData(value, sizeof(float));
}

bool Socket::readChar(char* value){
    return this->readData(value, sizeof(char));
}

bool Socket::readString(std::string* value) {
    int nbByes;
    if (!this->readInt(&nbByes)){
        return false;
    }
    char charArray[nbByes];
    if (!this->readData(charArray, nbByes * sizeof(char))) {
        return false;
    }
    *value = std::string(charArray, nbByes);
    return true;
}
