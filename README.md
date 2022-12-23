# Chat Room
![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)
![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)

A simple chat room application using only C/C++, with a server and a client program.

## Prerequisites
To run this project, you will need a C/C++ compiler. Some popular options include GCC and Clang.
> **Warning**
> This project is only supported on GNU/Linux since I use the epoll() function for I/O multiplexing.


## Installation
To get the project up and running on your local machine, follow these steps:
1. Clone the repository to your local machine
```
git clone https://github.com/lnfu/chat.git
```

2. Navigate to the project directory
```bash
cd chat
```

3. Compile the server and client programs using your C/C++ compiler
```bash
make
```

4. Run the server program in one terminal window
```bash
./build/server \<port\>
```

5. In another terminal window, run the client program
```bash
./build/client \<ip-address\> \<port\>
```

> **Note**
> If you do not assign the IP address and port number, the default IP address is localhost (127.0.0.1) and the default port number is 9999.

## Using the Chat Room
| Command                   | Description                                                                  |
| ------------------------- | ---------------------------------------------------------------------------- |
| mute                      | The user will not receive any message, including public and private message. |
| unmute                    | Disable mute                                                                 |
| yell <message>            | Send a message to others in the chat room.                                   |
| tell <receiver> <message> | Send a private message to <receiver> in the chat room.                       |
| Exit                      | Disconnect from the server.                                                  |

## Contributing
If you would like to contribute to the project, please fork the repository and make your changes in a separate branch. Once you are ready to submit your changes, open a pull request and describe your changes.

## License
This project is licensed under the MIT License - see the LICENSE file for details.
