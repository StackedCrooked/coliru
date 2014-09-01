#include <cstring>
#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: << " << argv[0] << " command\n";
        exit(0);
    }

    size_t cmd_size = 0;
    for (int i = 1; i != argc; ++i) {
        // + 1 for separating spaces
        cmd_size += strlen(argv[i]) + 1;
    }

    // create C string to hold the command to be executed
    char* cmd = new char[cmd_size];
    // index in the cmd C string to write to
    size_t cmd_ndx = 0;
    // copy argv[1] and all subsequent args to the cmd
    for (int i = 1; i != argc; ++i) {
        strcpy(&cmd[cmd_ndx], argv[i]);
        const size_t len = strlen(argv[i]);
        cmd_ndx += len;
        // separate with spaces
        cmd[cmd_ndx] = ' ';
        ++cmd_ndx;
    }
    // replace last space with null character
    cmd[cmd_ndx - 1] = '\0';

    std::cout << "The command is \"" << cmd << "\"\n";
    int return_value = system(cmd);
    delete[] cmd;
    std::cout << "The returned value was " << return_value << "\n";

    return 0;
}