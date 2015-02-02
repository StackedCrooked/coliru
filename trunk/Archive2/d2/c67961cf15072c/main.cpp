#include <iostream>

void foo(int &&x, int y = 0) {
    std::cout << &x << '\n';
}

int main() {
    foo(1);
}
