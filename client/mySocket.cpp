#include "mySocket.h"

bool MySocket::init(const char* socketPath) {
    sockaddr_un addr;
    char buffer;

    // Create a new client socket with domain: AF_UNIX, type: SOCK_STREAM, protocol: 0
    this->fd = socket(AF_UNIX, SOCK_STREAM, 0);

    if (this->fd == -1) {
        std::cerr << "ERROR: Failed to create socket" << std::endl;
        return false;
    }

    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, socketPath, sizeof(addr.sun_path) - 1);

    if (connect(this->fd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1) {
        std::cerr << "ERROR: Failed to connect to server socket. Make sure the server is running" << std::endl;
        return false;
    }
    return true;
}

bool MySocket::writeData(void* data, ssize_t size) {
    ssize_t nbBytesSent = size;
    ssize_t nbBytesLeft = size;
    while (nbBytesLeft > 0) {
        nbBytesSent = write(fd, data, size);
        nbBytesLeft = size - nbBytesSent;
        if (nbBytesSent == -1) {
            std::cerr << "ERROR: Failed to write data in server socket" << std::endl;
            return false;
        }
    }
    return true;
}

bool MySocket::writeInt(int value) {
    return this->writeData(&value, sizeof(int));
}

bool MySocket::writeFloat(float value) {
    return this->writeData(&value, sizeof(float));
}

bool MySocket::writeChar(char value) {
    return this->writeData(&value, sizeof(char));
}

bool MySocket::writeString(std::string value) {
    if (!this->writeInt(value.size())){
        return false;
    }
    if (!this->writeData((void*) value.c_str(), value.size() * sizeof(char))){
        return false;
    }
    return true;
}

bool MySocket::readData(void* data, ssize_t size) {
    ssize_t nbBytesread = size;
    ssize_t nbBytesLeft = size;
    while (nbBytesLeft > 0) {
        nbBytesread = read(this->fd, data, size);
        nbBytesLeft = size - nbBytesread;
        if (nbBytesread == -1) {
            std::cerr << "ERROR: haha Failed to read data from socket" << std::endl;
            return false;
        }
    }
    return true;
}

bool MySocket::readInt(int* value) {
    return this->readData(value, sizeof(int));
}
bool MySocket::readFloat(float* value) {
    return this->readData(value, sizeof(float));
}
bool MySocket::readChar(char* value){
    return this->readData(value, sizeof(char));
}
bool MySocket::readString(std::string* value) {
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