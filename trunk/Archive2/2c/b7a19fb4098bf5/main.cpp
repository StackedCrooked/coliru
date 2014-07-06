#include <string>

int main() {
    std::string* a = new std::string();
    a->~basic_string();
}