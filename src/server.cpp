#include <arpa/inet.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>

#include "../include/server_init.hpp"
#include "../include/utility.hpp"

using namespace std;


int main(int argc, char *argv[]) {
    int welcome_socket;

    int epoll_fd;
    int event_count;
    struct epoll_event *epoll_events;  // for trigger event

    // create socket
    // ! old
    // if (argc != 2) {
    //     printf("Usage : %s <port>\n", argv[0]);
    //     exit(1);
    // }
    // * new
    if (argc == 2) {
        welcome_socket = init_tcp_socket(argv[1]);
    } else {
        welcome_socket = init_tcp_socket("9999");
    }



    // epoll
    epoll_fd = epoll_create(EPOLL_SIZE);
    epoll_events = new epoll_event[EPOLL_SIZE];

    add_socket_to_epoll(welcome_socket, epoll_fd);


    // accept socket
    while (1) {
        event_count = epoll_wait(epoll_fd, epoll_events, EPOLL_SIZE, -1);  // -1: no timeout
        if (event_count == -1) {
            error_handling("epoll_wait()");
        }

        for (int i = 0; i < event_count; i++) {
            int fd = epoll_events[i].data.fd;

            if (fd == welcome_socket) {
                // create a new connection
                struct sockaddr_in client_address;
                socklen_t client_address_size = sizeof(client_address);

                int connect_socket = accept(welcome_socket, (struct sockaddr *)&client_address, &client_address_size);

                add_socket_to_epoll(connect_socket, epoll_fd);

                printf("Connected client: %d\n", connect_socket);
            } else {
                char buffer[BUFFER_SIZE] = {0};
                int receive_length = read(fd, buffer, BUFFER_SIZE);
                if (receive_length == 0) {
                    close_request(fd, epoll_fd);
                    printf("Closed client: %d\n", fd);
                } else {
                    // TODO
                    // !
                    write(fd, buffer, receive_length);
                }
            }
        }
    }

    // close fd
    close(welcome_socket);
    close(epoll_fd);

    return 0;
}