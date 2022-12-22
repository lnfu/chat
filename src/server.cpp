#include <arpa/inet.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>

#include "../include/server_init.hpp"

using namespace std;

#define TRUE 1
#define FALSE 0
#define EPOLL_SIZE 50

void error_handling(const char *error_message) {
    perror(error_message);
    exit(1);
}

int main(int argc, char *argv[]) {
    int tcp_socket;
    int udp_socket;

    int epoll_fd;
    int event_count;
    struct epoll_event *epoll_events;
    struct epoll_event event;

    struct sockaddr_in client_address;

    if (argc != 2) {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    // create socket
    tcp_socket = init_tcp_socket(argv[1]);
    udp_socket = init_udp_socket(argv[1]);

    // epoll
    epoll_fd = epoll_create(EPOLL_SIZE);
    epoll_events = malloc(sizeof(struct epoll_event) * EPOLL_SIZE);

    event.events = EPOLLIN;
    event.data.fd = tcp_socket;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, tcp_socket, &event);

    // accept socket

    // close socket
    close(tcp_socket);
    close(udp_socket);

    return 0;
}