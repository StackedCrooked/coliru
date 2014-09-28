#include <iostream>

int main() {
    int &&r = 5;
    r = 7;
    std::cout << r;
}