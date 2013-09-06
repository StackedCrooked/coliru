#include <iostream>
#include <cassert>

void f(unsigned x) {
    assert(x >= 0);
    std::cout << x;
}

void g(int x) {
    assert(x >= 0);
    std::cout << x;
}

int main() {
    f(-2);
    g(-2);
}