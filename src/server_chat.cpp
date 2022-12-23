#include <unistd.h>

#include <cstdio>
#include <cstring>
#include <unordered_map>

#include "../include/utility.hpp"

using namespace std;

void mute(int id, unordered_map<int, bool> &user_is_mute) { user_is_mute[id] = true; }
void unmute(int id, unordered_map<int, bool> &user_is_mute) { user_is_mute[id] = false; }

void yell(int id, char *buffer, unordered_map<int, int> &user_fd, unordered_map<int, bool> &user_is_mute) {
    char message[MESSAGE_SIZE] = {0};
    sscanf(buffer, "yell %[^\n]", message);

    memset(buffer, 0, BUFFER_SIZE);

    sprintf(buffer, "user%d: %s", id, message);

    for (auto [receive_id, receive_fd] : user_fd) {
        if (user_is_mute[receive_id]) continue;

        write(receive_fd, buffer, BUFFER_SIZE);
    }
}

void tell(int id, char *buffer, unordered_map<int, int> &user_fd, unordered_map<int, bool> &user_is_mute) {
    int receive_id;
    char message[MESSAGE_SIZE] = {0};
    sscanf(buffer, "tell user%d %[^\n]", &receive_id, message);

    memset(buffer, 0, BUFFER_SIZE);

    if (user_fd.find(receive_id) == user_fd.end()) {
        sprintf(buffer, "user%d does not exist", receive_id);
        write(user_fd[id], buffer, BUFFER_SIZE);
        return;
    }

    sprintf(buffer, "user%d told you: %s", id, message);
    write(user_fd[receive_id], buffer, BUFFER_SIZE);
}