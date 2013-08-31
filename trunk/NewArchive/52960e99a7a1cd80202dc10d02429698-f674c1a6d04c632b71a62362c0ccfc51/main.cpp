#include <iostream>

int main() {
    int a = 10 << 16 | 12 << 8;
    int b = a >> 16;
    int c = a >> 8;
    std::cout << a << ' ' << b << ' ' << c;
}