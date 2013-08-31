#include <iostream>

int f() {
    auto g = [](int x) { return x + 5; };
    return g(100);
}

int main() {
    std::cout << f();
}