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
        std::cerr << "I'm a parent!\n";
    else if (pid == -1)
        std::cerr << "Failed :'(\n";
    else
        std::cerr << "Baaababa\n";
}