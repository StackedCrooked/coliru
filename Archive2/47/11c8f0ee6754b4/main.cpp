#include <iostream>

int main() {
    int x = 5;
    unsigned y = static_cast<unsigned>(-1) * x;
    unsigned z = -5;
    std::cout << x << '\n' << y << '\n' << z;
}
