#include <iostream>

struct A {
    A() { std::cout << "construct\n"; }
};

int main(int argc, char **argv) {
    new (0) A();
    return 0;
}