#include <iostream>

enum t : int { a = 1, b, c };

void test(int& x) {
    x = 2;
}

int main() {
    int x = a;
    std::cout << (x == a) << '\n';
    test(x);
    std::cout << (x == b) << '\n';
}