#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>

using namespace std;

#define TRUE 1
#define FALSE 0

void error_handling(const char *error_message) {
    perror(error_message);
    exit(1);
}

/// @brief set address of server (INADDRANY)
/// @param server_address
/// @param port
void set_server_address(struct sockaddr_in *server_address, const char *port) {
    server_address->sin_family = AF_INET;
    server_address->sin_addr.s_addr = htonl(INADDR_ANY);
    server_address->sin_port = htons(atoi(port));
}

/// @brief TCP socket: create, bind, listen
/// @param port
/// @return file descriptor of TCP socket
int init_tcp_socket(const char *port) {
    int tcp_socket;
    int option;

    struct sockaddr_in server_address;

    // create socket
    tcp_socket = socket(PF_INET, SOCK_STREAM, 0);
    if (tcp_socket == -1) {
        error_handling("socket()");
    }

    // set SO_REUSEADDR = TRUE
    option = TRUE;
    setsockopt(tcp_socket, SOL_SOCKET, SO_REUSEADDR, (void *)&option, sizeof(option));

    // set address
    set_server_address(&server_address, port);

    // bind
    if (bind(tcp_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        error_handling("bind()");
    }

    // listen
    if (listen(tcp_socket, 15) == -1) {
        error_handling("listen()");
    }

    printf("TCP is running\n");

    return tcp_socket;
}

/// @brief UDP socket: create, bind
/// @param port
/// @return file descriptor of UDP socket
int init_udp_socket(const char *port) {
    int udp_socket;
    int option;

    struct sockaddr_in server_address;

    // create socket
    udp_socket = socket(PF_INET, SOCK_DGRAM, 0);
    if (udp_socket == -1) {
        error_handling("socket()");
    }

    // set SO_REUSEADDR = TRUE
    option = TRUE;
    setsockopt(udp_socket, SOL_SOCKET, SO_REUSEADDR, (void *)&option, sizeof(option));

    // set address
    set_server_address(&server_address, port);

    // bind
    if (bind(udp_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        error_handling("bind()");
    }

    printf("UDP is running\n");

    return udp_socket;
}
