#include <functional>
#include <iostream>

std::function<int()> fib() {
    auto a = new int(0);
    auto b = new int(1);
    return [=] () -> int {
        auto x = *a + *b;
        *a = *b;
        *b = x;
        return *a;
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
