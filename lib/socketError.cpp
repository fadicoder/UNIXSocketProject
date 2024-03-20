#include "socketError.h"

const char* getErrorDescription(SocketError error){
    switch (error) {
    case SocketError::NO_ERROR:
        return "";
    case SocketError::FAILED_CONNECTION:
        return "Could not connect to server. Make sure server is running and socket path is valid";
    case SocketError::FAILED_LISTEN:
        return "Failed to list on socket";
    case SocketError::FAILED_BIND:
        return "Failed to bind to socket";
    case SocketError::FAILED_SOCKET_CREATION:
        return "Failed create socket";
    case SocketError::FAILED_SOCKET_REMOVE:
        return "Could not remove existing socket";
    case SocketError::LONG_PATH:
        return "Socket path is too long";
    default:
        return "Undocumented error";
    }
}