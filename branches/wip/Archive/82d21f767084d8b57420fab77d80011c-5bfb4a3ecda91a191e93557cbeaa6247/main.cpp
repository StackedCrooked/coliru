#include <iostream>

struct Foo {
    Foo() {
        throw 5;
    }
};

int main() {
    try {
        static Foo foo;
    } catch (int) {
        std::cout << "That source is wrong.";
    }
}