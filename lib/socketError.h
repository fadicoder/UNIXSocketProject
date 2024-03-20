#ifndef SOCKET_ERROR
#define SOCKET_ERROR

enum class SocketError {
    NO_ERROR = 0,
    FAILED_SOCKET_CREATION,
    LONG_PATH,
    FAILED_CONNECTION,
    FAILED_SOCKET_REMOVE,
    FAILED_BIND,
    FAILED_LISTEN,
};

const char* getErrorDescription(SocketError error);

#endif // SOCKET_ERROR