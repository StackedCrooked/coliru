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
    Derived d{};
    std::cout << "d.i = " << d.i << "  " << "d.j = " << d.j << '\n';
}