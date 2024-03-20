#ifndef SERVER_H
#define SERVER_H

#include <sys/un.h>
#include "socketError.h"
#include "socket.h"

class Server {
private:
    int fd;

public:
    Server();
    ~Server();
    SocketError start(const char* socketPath, const uint maxConnections);
    Socket* acceptClient();
};

#endif // SERVER_H