#include <iostream>
#include <array>
#include <memory>


void do_something(std::array<int, 5>) {}

int main() {
    do_something( {{ 1, 2, 3, 4, 5 }} );
    std::cout << "compiled\n";
}