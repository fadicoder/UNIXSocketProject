#include <iostream>
#include "command.h"

int main(int argc, char** argv) {
    Command command = Command("git", 2, "rev-parse", "HEAD");
    command.execute();
    command.waitExecution();
    size_t size = -1;
    while (size > 0) {
        char output;
        size = command.readStdout(&output, 1);
        std::cout << output;
    }

    // int fd[2];
    // pipe(fd);
    // if (fork() == 0) {
    //     dup2(fd[1], 1);
    //     close(fd[0]);
    //     close(fd[1]);
    //     char* args[4] = {"git", "rev-parse", "HEAD", NULL};
    //     execvp("git", args);
    //     _exit(0);
    // }
    // size_t size = -1;
    // close(fd[1]);
    // while (size > 0) {
    //     char a;
    //     size = read(fd[0], &a, 1);
    //     std::cout << a;
    // }
    // std::cout << std::endl;
    // close(fd[0]);
}