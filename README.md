# Unix socket project

This project contains 2 applications: Client and Server. Theses applications communicate over a UNIX stream socket. The Client application will send text commands to the server and printout the server response. The server listens for clients connection of a UNIX socket and responds to its commands.

## Getting Started


### Prerequisites

Requirements to build the project:
- make
- g++
- ar
- aarch64-linux-g++ (only if cross compiling with aarch64)
- aarch64-linux-ar (only if cross compiling with aarch64)

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
To start the server, run the following command from the project root directory:
```bash
./server/build/server socket.sock
```
The server require 1 command line argument which is the path to the the UNIX socket. This command will create a socket file named socket.sock in the project root directory.

### running the client
To start the client, run the following command from the project root directory:
```bash
./client/build/client socket.sock VERSION
```

The command above will printout the last commit id in your local repository.

The client require one argument which is the path to the socket by the server. The remaining arguments will be sent as separate commands to the server. If no commands are provided, the client will run in shell mode and read commands from the command line.

### Running with docker container

from terminal A, run the following commands:
```bash
sudo docker build -t image .
sudo run it image bash
```

from terminal B, run the following command:
```bash
sudo docker ps
```

This should print the container id of the image we just ran in terminal A. We will join that session using this container id.
```bash
sudo docker exec -it <CONTAINER_ID> bash
```

Now we can run the client and the server from terminals A and B as described in the previous sections.

### Possible commands
Here is a list of possible commands:

- VERSION: Will return the last commit id

**All commands are case sensible**
