#include <iostream>
#include <string>
#include <vector>

struct B {
    B(int arg) {
        std::cout << "In non-default constructor " << arg << "\n";
    }
};
struct A {
    B b;
    A() : b(5) {
        std::cout << "In A constructor body.";
    }
};
int main() {
    A a;
}