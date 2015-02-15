#include <iostream>

struct B { };
struct D : B { };

template<typename T>
void f(T x) {
    std::cout << "A:" << x << '\n';
}

void f(B* x) {
    std::cout << "B: " << x << '\n';
}

int main() {
    f(42);
    f(new B);
    f(new D);
    return 0;
}