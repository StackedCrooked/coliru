#include <iostream>
#include <random>

int main(int, char*[]) {
    long double u = rand() / (RAND_MAX + 1.0);
    std::cout << u << '\n';
    return 0;
}