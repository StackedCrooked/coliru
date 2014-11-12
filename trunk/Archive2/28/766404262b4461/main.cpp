#include <iostream>
#include <functional>

int main() {
    int k = 0;
    std::function<void()> cycle = [=]() mutable {
        k++;
        std::cout << k << std::endl;
    };
    cycle();
}