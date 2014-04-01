#include <iostream>
#include <utility>

struct foo {
    foo() = default;
    foo(foo const&) { std::cout << "foo(const&)\n"; }
    foo(foo&&) { std::cout << "foo(&&)\n"; }
};

foo f() {
    std::cout << "f()\n";
    foo obj;
    return obj;
}

foo g() {
    std::cout << "g()\n";
    foo obj;
    return std::move(obj);
}

int main() {
    auto&& x = f();
    auto&& y = g();
}