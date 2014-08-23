#include <iostream>
#include <string>

void print_strings() { /* Do Nothing */ }

template <typename... Args>
void print_strings(std::string str, Args... args) {
    std::cout << str << ", ";
    print_strings(args...);
}

int main() {
    print_strings("Lel", "Wot", "Lelling");
}
