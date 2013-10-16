#include <stdexcept>
#include <string>

struct file_not_found : std::runtime_error {
    file_not_found(const std::string& str): std::runtime_error(str + " not found") {}
};

bool open_file(std::string) { return false; }

int main() {
    if(!open_file("hello.txt"))
        throw file_not_found("hello.txt");
}
