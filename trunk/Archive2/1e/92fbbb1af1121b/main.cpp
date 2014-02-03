#include <iostream>

struct S {
    int x;

    S(int x_) : x(x_) { }

    S& f() {
        S& result = *this;
        std::cout << ++x << '\n';
        return result;
    }

    S g() {
        S result = *this;
        std::cout << ++x << '\n';
        return result;
    }
};

int main() {
    S a(0);
    a.f().f();

    a.g().g();

    return 0;
}
