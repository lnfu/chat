#include <unordered_map>

using namespace std;

void mute(int id, unordered_map<int, bool> &user_is_mute);
void unmute(int id, unordered_map<int, bool> &user_is_mute);
void yell(int id, char *buffer, unordered_map<int, int> &user_fd, unordered_map<int, bool> &user_is_mute);
void tell(int id, char *buffer, unordered_map<int, int> &user_fd, unordered_map<int, bool> &user_is_mute);