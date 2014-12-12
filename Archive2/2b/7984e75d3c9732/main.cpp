#include <functional>
#include <iostream>

int main() {
    std::function<void()> f = [] {
        std::cout << "hi\n";
    };

    f();

    f = [] {
        std::cout << "bye\n";
    };

    f();

    return 0;
}