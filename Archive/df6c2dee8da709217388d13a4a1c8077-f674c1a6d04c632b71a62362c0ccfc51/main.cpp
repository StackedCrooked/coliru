#include <iostream>

int foo(int x) {
    struct bar {
        int getX() {
            return x;
        }
    };
    return bar().getX();
}

int main() {
    std::cout << foo(42) << '\n';
}
