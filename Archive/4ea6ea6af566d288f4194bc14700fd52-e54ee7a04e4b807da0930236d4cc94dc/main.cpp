#include <iostream>

class X {
public:
    void f();
};

auto X::f() -> decltype(f()) {
    std::cout << "Hello Xeo, I win.";
}

int main() {
    X x;
    x.f();
}