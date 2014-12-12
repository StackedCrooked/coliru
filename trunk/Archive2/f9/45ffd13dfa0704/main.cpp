#include <functional>
#include <iostream>

template<typename F>
void x(F g) {
    g();
}

int main() {
    std::function<void()> f = [] {
        std::cout << "hi\n";
    };

    x(f);

    f = [] {
        std::cout << "bye\n";
    };

    x(f);

    x([] {
        std::cout << "hey man what's up anonymous functions are great\n";
    });

    return 0;
}