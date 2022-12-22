#include <iostream>

void error_handling(const char *error_message) {
    perror(error_message);
    exit(1);
}