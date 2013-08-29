#include <iostream>

int main() {
someLabel:
    auto lambda = [] {
        goto someLable;
        std::cout << "Hello, world!\n";
    };
    lambda();
}
