#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

#include "../include/utility.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    int client_socket = socket(PF_INET, SOCK_STREAM, 0);

    if (client_socket == -1) {
        error_handling("socket()");
    }

    // ! old
    // if (argc != 3) {
    //     printf("Usage : %s <ip-address> <port>\n", argv[0]);
    //     exit(1);
    // }
    // *new
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    if (argc == 3) {
        address.sin_addr.s_addr = inet_addr(argv[1]);
        address.sin_port = htons(atoi(argv[2]));
    } else {
        address.sin_addr.s_addr = inet_addr("127.0.0.1");
        address.sin_port = htons(9999);
    }

    if (connect(client_socket, (struct sockaddr *)&address, sizeof(address)) == -1) {
        error_handling("connect()");
    }

    printf("TCP connection has created\n");

    while (TRUE) {
        cout << "% ";

        char buffer[BUFFER_SIZE] = {0};

        fgets(buffer, BUFFER_SIZE, stdin);

        printf("Sending message: %s", buffer);

        write(client_socket, buffer, strlen(buffer) - 1);  // -1 is because i dont want the \n

        memset(buffer, 0, BUFFER_SIZE);

        read(client_socket, buffer, BUFFER_SIZE);

        printf("Received message: %s\n", buffer);
    }

    close(client_socket);

    return 0;
}