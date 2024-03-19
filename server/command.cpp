#include "command.h"

Command::Command(const char* name, uint nbArgs,...){
    this->name = (char*) name;
    this->args = new char*[nbArgs + 2];
    this->args[0] = this->name;
    this->hasStarted = false;

    va_list argList;
    va_start(argList, nbArgs);
    for(int i = 0; i < nbArgs; i++){
        this->args[i+1] = va_arg(argList, char*);
    }
    va_end(argList);

    this->args[nbArgs + 1] = (char*) NULL;
}

Command::~Command(){
    delete this->args;
    close(this->childStdIn);
    close(this->childStdOut);
    close(this->childStdError);
    this->sendSignal(SIGKILL);
}

void Command::waitExecution(){
    waitpid(processPid, &status, 0);
}

void Command::execute(){
    if(this->hasStarted){
        this->waitExecution(); // Wating for last execution to finish before starting a new one.
        close(this->childStdIn);
        close(this->childStdOut);
        close(this->childStdError);
    }
    int inputPipe[2];
    int outputPipe[2];
    int errorPipe[2];
    pipe(inputPipe);
    pipe(outputPipe);
    pipe(errorPipe);
    this->processPid = fork();
    if(this->processPid == 0){ // child process
        dup2(outputPipe[1], 1);
        dup2(errorPipe[1], 2);
        dup2(inputPipe[0], 0);
        close(inputPipe[0]);
        close(inputPipe[1]);
        close(outputPipe[0]);
        close(outputPipe[1]);
        close(errorPipe[0]);
        close(errorPipe[1]);
        execvp(this->name, this->args);
    }
    close(outputPipe[1]);
    close(errorPipe[1]);
    close(inputPipe[0]);
    this->childStdIn = inputPipe[1];
    this->childStdOut = outputPipe[0];
    this->childStdError = errorPipe[0];
    this->hasStarted = true;
}

ssize_t Command::readStdout(void* buffer, size_t nbBytes){
    return read(this->childStdOut, buffer, nbBytes);
}

ssize_t Command::readStderr(void* buffer, size_t nbBytes){
    return read(this->childStdError, buffer, nbBytes);
}

ssize_t Command::writeStdin(void *__buf, size_t __nbytes){
    return write(this->childStdIn, __buf, __nbytes);
}

bool Command::exitedNormaly(){
    waitExecution();
    return WIFEXITED(this->status);
}

int Command::getExitStatus(){
    waitExecution();
    return WEXITSTATUS(this->status);
}

int Command::getStatus(){
    waitExecution();
    return status;
}

int Command::sendSignal(int sig) {
    return kill(this->processPid, sig);
}
