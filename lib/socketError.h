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

/**
 * @return a message that describes the error or a empty string of error is SocketError::NO_ERROR
*/
const char* getErrorDescription(SocketError error);

#endif // SOCKET_ERROR