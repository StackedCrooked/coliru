#include <iostream>

auto foo(int x) {
    struct bar {
        int x;
        int getX() {
            return x;
        }
    };
    return bar{x};
}

int main() {
    std::cout << foo(42).getX() << '\n';
}
