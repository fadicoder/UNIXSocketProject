#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h>
#include <sys/un.h>
#include <iostream>
#include <unistd.h>
#include <pthread.h>

class MySocket {
private:
    sockaddr_un address;
    int fd;

public:
    bool init(const char* socketPath);
    bool create(const char* socketPath);

    bool writeData(void* data, ssize_t size);
    bool writeInt(int value);
    bool writeFloat(float value);
    bool writeChar(char value);
    bool writeString(std::string value);

    bool readData(void* data, ssize_t size);
    bool readInt(int* value);
    bool readFloat(float* value);
    bool readChar(char* value);
    bool readString(std::string* value);

    bool acceptClient(void* handleClient(MySocket*));
};
#endif // SOCKET_H
