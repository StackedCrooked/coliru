#include <iostream>

struct A {
    A() {}
    A(int x) { std::cout << "constructed: " << x << "\n"; }
};

int main(int argc, char **argv) {
    A a;

    new (0) A(0);
    new (&a) A(1);

    return 0;
}