#include <functional>
#include <iostream>

std::function<int()> fib() {
    auto a = int(0);
    auto b = int(1);
    return [=] () mutable -> int {
        auto x = a + b;
        a = b;
        b = x;
        return a;
    };
}

int main() {
    auto f = fib();
    std::cout << f() << '\n';
    std::cout << f() << '\n';
    std::cout << f() << '\n';
    std::cout << f() << '\n';
    std::cout << f() << '\n';
    std::cout << f() << '\n';
    std::cout << f() << '\n';
    std::cout << f() << '\n';
    std::cout << f() << '\n';
}
