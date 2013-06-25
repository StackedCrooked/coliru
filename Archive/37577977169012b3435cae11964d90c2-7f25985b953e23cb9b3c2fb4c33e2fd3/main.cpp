#include <iostream>
#include <unistd.h>

struct dangerous_resource {
    dangerous_resource() {
        std::cout << "Setting up important resource\n";
    }

    dangerous_resource(dangerous_resource const&) = delete;

    ~dangerous_resource() {
        std::cout << "Deleting a dangerous resource\n";
    }
};

dangerous_resource dr;

int main() {
    auto pid = fork();

    if (pid == 0)
        std::cout << "I'm a parent!\n";
    else if (pid == -1)
        std::cout << "Failed :'(\n";
    else
        std::cout << "Baaababa\n";
}