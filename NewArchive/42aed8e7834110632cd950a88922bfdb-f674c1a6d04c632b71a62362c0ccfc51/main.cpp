#include <iostream>

int main() {
    [] {
        someLabel:
        std::cout << "Hello, world!\n";
        goto someLabel;
    }();
}
