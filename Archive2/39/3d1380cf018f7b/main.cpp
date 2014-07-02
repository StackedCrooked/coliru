#include <iostream>

int main() {
    for(char c = 0x20; c < 0x7f; ++c) {
        std::cout << c << '\n';
    }
}