#include <iostream>

void print(unsigned x, unsigned y) {
    std::cout << static_cast<unsigned>(x) << "\n" << static_cast<unsigned>(y);
}

int main() {
    int x = 10;
    int y = -19;
    print(x, y);
}