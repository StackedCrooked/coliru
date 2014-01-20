#include <iostream>
struct Base {
    int i;

    Base(int i):i(i) {}
    Base():i(10) {}
};

struct Derived : public Base {
    int j;

    Derived(int j):Base(j), j(j) {}
    Derived()=default;
};

int main() {
    std::cout << __VERSION__ << '\n';
    Derived d{42};
    ::new (&d) Derived{};
    std::cout << "d.i = " << d.i << "  " << "d.j = " << d.j << '\n';
}