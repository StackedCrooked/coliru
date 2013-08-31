#include <iostream>

int main() {
    unsigned x = 8;
    std::cout << (x ^ (0xD3ADBEEF & 0xC1CADA5));
}
