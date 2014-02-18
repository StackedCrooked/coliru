#include <iostream>

int f(const int);

int f(int i) { return i + 1; }


int main() {
    std::cout << f(3) << '\n';
}