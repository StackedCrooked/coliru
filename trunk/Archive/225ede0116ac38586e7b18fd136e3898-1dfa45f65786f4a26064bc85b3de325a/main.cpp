#include <iostream>

struct S {
    S() {
        std::cout << "Initialized\n";
    }
};

void foo() {
    static S s;
}

int main() {
    std::cout << "Begin main\n";
    foo();
    std::cout << "End main\n";
}