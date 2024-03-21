# Unix socket application

This project contains 2 application: Client and Server. Theses applications communicate over a UNIX stream socket.

## Getting Started


### Prerequisites

Requirements to build the project:
- make
- g++
- ar
- aarch64-linux-gnu-g++ (only if cross compiling with aarch64)
- aarch64-linux-gnu-ar (only if cross compiling with aarch64)

Requirements to run the project:
- git

### Installing

Run the following commands to build the project with system architecture:
```bash
cd lib
make
cd ../server
make
cd ../client
make
```

For cross-compilation with aarch64 run the following commands:
```bash
cd lib
make ARCH=aarch64
cd ../server
make ARCH=aarch64
cd ../client
make ARCH=aarch64
```

### running the server
To run the server execute the binary file in "server/build/server". Make sure that you are executing the program from a directory which is part of a git repository otherwise the VERSION command will not work. 

The program require 1 command line argument which is the path to the the UNIX socket. The socket will be created if not already present.

### running the client
To run the client execute the binary file "client/build/client". Make sure you have started the server before running the client.

The program require one argument which is the path to the socket used when starting the server. If no other arguments are provided, the client will run in shell mode. Otherwise it will send each argument as a separate command to the server.

## Possible commands
Here is a list of possible commands:

- VERSION: Will return the last commit id

**The commands above are case sensible**
