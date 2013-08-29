#include <iostream>

int main() {
someLabel:
    auto lambda = [] {
        goto someLabel;
        std::cout << "Hello, world!\n";
    };
    lambda();
}
