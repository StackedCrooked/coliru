#include <string>
#include <unistd.h>

int main() {
    std::string message("Hello, world!\n");
    write(STDOUT_FILENO, message.data(), message.size());
    return 0;
}
