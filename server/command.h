
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <vector>
#include <stdarg.h>


class Command{
private:
    char** args;
    char* name;

    pid_t processPid;
    int childStdIn;
    int childStdOut;
    int childStdError;
    bool hasStarted;
    bool isDone;
    int status;

public:
    Command(const char* name, uint nbArgs,...);

    ~Command();

    void execute();

    ssize_t readStdout(void * buffer, size_t nbBytes);

    ssize_t readStderr(void *__buf, size_t __nbytes);

    ssize_t writeStdin(void *__buf, size_t __nbytes);

    void waitExecution();

    bool exitedNormaly();

    int getExitStatus();

    int getStatus();
    
    int sendSignal(int sig);
};