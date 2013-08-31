#include <functional>
#include <iostream>

std::function<unsigned long long()> fib() {
    auto a = 0ull, b = 1ull;
    return [=] () mutable -> unsigned long long {
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
