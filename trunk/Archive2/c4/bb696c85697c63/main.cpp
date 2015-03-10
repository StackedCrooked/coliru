#include <utility>
#include <iostream>

template<typename T, typename U = decltype(f(std::declval<T>()))>
void g(const T&) { std::cout << "g generic\n"; }

struct test {};

void g(const test&) {
    std::cout << "g test\n";
}

// make it 'ambiguous'
void f(const test&) {}

struct other {};
void f(const other&) {}

int main() {
    g(test{});
    g(other{});
}
