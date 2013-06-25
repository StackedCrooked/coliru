#include <iostream>
#include <unistd.h>

struct dangerous_resource {
    dangerous_resource() {
        std::cerr << "[" << getpid() << "] Setting up important resource\n";
    }

    dangerous_resource(dangerous_resource const&) = delete;

    ~dangerous_resource() {
        std::cerr << "[" << getpid() << "] Deleting a dangerous resource\n";
    }
};

int main() {
    dangerous_resource dr;

    auto pid = fork();

    if (pid == 0)
        std::cerr << "[" << getpid() << "] Baaababa\n";
    else if (pid == -1)
        std::cerr << "[" << getpid() << "] Failed :'(\n";
    else
        std::cerr << "[" << getpid() << "] I'm a parent!\n";
}