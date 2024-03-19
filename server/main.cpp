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
}