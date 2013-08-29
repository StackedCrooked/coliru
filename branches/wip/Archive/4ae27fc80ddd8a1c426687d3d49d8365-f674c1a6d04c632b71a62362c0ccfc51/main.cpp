#include <iostream>

struct A {
    int b;
    A(int c): b(c) {}
    
    int& operator*() {
        std::cout << "int&\n";
        return b;
    }
    
    const int& operator*() const {
        std::cout << "const int&\n";
        return b;
    }
};

struct B {
    A a;
    B(int c): a(c) {}
    auto operator*() -> decltype(*a) {
        return *a;
    }
};

void f(const int& g) {
    std::cout << "...\n";
}

int main() {
    B b(10);
    f(*b);
}