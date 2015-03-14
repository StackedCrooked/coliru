#include <exception>
#include <string>
#include <memory>

struct A {
    A(int i) : i(i) { }
    int i;
};

struct B : virtual A {
    B(int i) : A(i) { }
};

struct C : virtual B {
    C(int i) : B(i) { }
};

int main(int argc, char** argv) {
    C c(5);
    return 0;
}