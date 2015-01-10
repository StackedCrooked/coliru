#include <iostream>

struct Foo {
    void qux() {
        std::cout << "non volatile\n";
    }
    void qux() volatile {
        std::cout << "volatile\n";
    }
};

int main() {
    Foo non_v;
    volatile Foo v;
    non_v.qux();
    v.qux();
    return 0;
}