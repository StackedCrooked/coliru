#include <limits>
#include <iostream>

int main() {
    std::cout << (0.1 - std::numeric_limits<double>::epsilon()) * 10;
}