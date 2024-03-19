
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
    int status;

public:
    Command(const char* name, uint nbArgs,...);

    ~Command();

    /**
     * This function executes the command in a child process.
     * 
     * Note: when running this function multiple times, the function waits for last execution to finish before starting a new one.
    */
    void execute();

    /**
     * This function is for reading the standard output of the currently running command. The function will block until 
     * the running command outputs the specified number of bytes into its standard output.
     * 
     * @returns the number of bytes read or -1 in case of error
    */
    ssize_t readStdout(void * buffer, size_t nbBytes);

    /**
     * This function is for reading the standard error of the currently running command. The function will block until 
     * the running command outputs the specified number of bytes into its standard error.
     * 
     * @returns the number of bytes read or -1 in case of error
    */
    ssize_t readStderr(void *__buf, size_t __nbytes);

    /**
     * This function writes data in the standard input of the command
     * 
     * @returns the number of bytes written or -1 in case of error
    */
    ssize_t writeStdin(void *__buf, size_t __nbytes);

    /**
     * This function block until the command program exists
    */
    void waitExecution();

    bool exitedNormally();

    int getExitStatus();

    int getStatus();
    
    int sendSignal(int sig);

private:
    void executeChildProcess(int inputPipe[], int outputPipe[], int errorPipe[]);

    void setupParentPipes(int inputPipe[], int outputPipe[], int errorPipe[]);

    void closePipes();
};