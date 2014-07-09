#include <iostream>
struct B;

struct A {
    B const &b;
};

struct B : A {
    B() : A(*this) {}
};

int main() {
    B b;
    std::cout << "Works!\n";
}
