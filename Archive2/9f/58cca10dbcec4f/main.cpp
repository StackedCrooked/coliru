#include <iostream>

int main() {
    auto fun = [] {
        int i = 0;
        auto counter = [&]() {
            return ++i;
        };
        return counter;
    };
    auto fn = fun();
    for (int i = 0; i < 10; ++i) {
        std::cout << fn() << ' ';
    }
}
