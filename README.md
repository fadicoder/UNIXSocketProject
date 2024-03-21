# Unix socket application

This project contains 2 application: Client and Server. Theses applications communicate over a UNIX stream socket. The Client application will send text commands to the Server and the server will respond with a text message. 

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
./server/build/server
```
The server require 1 command line argument which is the path to the the UNIX socket. The socket will be created if not already present.

### running the client
To start the client, run the following command from the project root directory:
```bash
./client/build/client
```

The client require one argument which is the path to the socket used when starting the server. The remaining arguments will be sent as separate commands to the server. If no commands are provided, the client will run in shell mode and will read commands from the command line.

### Running with docker container

from terminal A run the following commands:
```bash
sudo docker build -t image .
sudo run it image bash
```

from terminal B the command
```bash
sudo docker ps
```
This should show the container id of the image we just ran in terminal A. We will join that session using this container id.
```bash
sudo docker exec -it <CONTAINER ID> bash
```

Now we can run the client and the server as described in the previous sections.

### Possible commands
Here is a list of possible commands:

- VERSION: Will return the last commit id

Unknown commands will be responded with "REJECTED"

**The commands above are case sensible**
