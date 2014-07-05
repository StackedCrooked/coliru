#include <iostream>

auto func(int x) {
    return [=](int y) {
            return [=](int z) {
                return x * y * z;
            };
    };
}

int main() {
    std::cout << func(10)(11)(12);
}