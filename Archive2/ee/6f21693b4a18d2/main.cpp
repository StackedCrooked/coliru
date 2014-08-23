#include <iostream>
#include <string>
#include <initializer_list>

void print_strings(std::initializer_list<std::string> args) {
    for (auto arg: args) {
        std::cout << arg << ", ";
    }
}

int main() {
    print_strings({"Lel", "Wot", "Lelling"});
}
