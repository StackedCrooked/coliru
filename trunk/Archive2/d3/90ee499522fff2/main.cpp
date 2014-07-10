#include <iostream>
#include <functional>

void foo() {
    std::cout << "foo\n";
}

void bar() {
    std::cout << "bar\n";
}

void foobar() {
    std::cout << "foobar\n";
}

void qux(int t) {
    std::cout << t << "\n";
}

void qux(double t) {
    std::cout << t << "\n";
}

template<class T>
decltype(auto) operator*(T& f) {
    return [&](auto&&... a) -> decltype(auto){return f(std::forward<decltype(a)>(a)...);};
}

int main() {
    auto f = *foobar;
    f();
    auto f2 = *qux;
    f2(300);
    return 0;
}