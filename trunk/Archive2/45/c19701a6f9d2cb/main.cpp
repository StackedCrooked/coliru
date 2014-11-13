#define _POSIX_C_SOURCE 200112L
#include <cmath>
#include <iostream>

int main() {
    std::cout << 1./0. << '\n';
    return 0;
}