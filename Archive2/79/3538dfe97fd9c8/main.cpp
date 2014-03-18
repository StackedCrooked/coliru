#include <iostream>

int main() {
    int* x = new int[5];
    int* y = new int[5];
    std::cout << x << ',' << y << '\n';
    x = y;
    std::cout << x << ',' << y << '\n';
}