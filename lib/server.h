#ifndef SERVER_H
#define SERVER_H

#include <sys/un.h>
#include "socketError.h"
#include "socket.h"

#define DEFAULT_MAX_CONNECTIONS 1

class Server {
private:
    int fd;

public:
    Server();

    ~Server();

    /**
     * This function will start the server application by initializing a UNIX socket in the specified path.
     * If the path does not exist, it will create a new file, otherwise it will replace the file already present.
     * The server allows only 1 connection of the maxConnections argument is not specified.
     * @returns an instance of SocketError representing the error
    */
    SocketError start(const char* socketPath, const uint maxConnections = DEFAULT_MAX_CONNECTIONS);

    /**
     * This function will wait for a new client to connect. It is a blocking function.
     * The function should be called after start() method.
     * @returns A pointer to the socket instance used to communicated with the connected client.
    */
    Socket* acceptClient();
};

#endif // SERVER_H