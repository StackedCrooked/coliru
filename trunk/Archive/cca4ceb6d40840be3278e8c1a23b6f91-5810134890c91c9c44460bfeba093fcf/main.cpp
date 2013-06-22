#include <iostream>

struct foo {
    void operator+() {
        std::cout << "foo::operator+\n";
    }
};

struct bar: foo {
    void operator+() {
        std::cout << "bar::operator+\n";
    }
};

int main() {
    bar b; 
    +b;
}