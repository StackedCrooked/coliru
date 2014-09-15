#include <memory>
#include <functional>
#include <iostream>
int foo(int a) { std::cout << a << std::endl; return a + 1; }
void bar(int a, int b) { std::cout << a << ' ' << b << std::endl; }
int main() {
    auto f = std::bind(foo, std::placeholders::_1);
    auto g = std::bind(bar, f, std::placeholders::_1);
    g(1);
}