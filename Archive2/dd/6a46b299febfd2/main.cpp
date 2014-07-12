#include <iostream>

struct S {
    S() {}
    
    void foo() {std::cout << "none\n";}
    void foo() const {std::cout << "const\n";}
    void foo() volatile {std::cout << "volatile\n";}
    void foo() const volatile {std::cout << "const volatile\n";}
};

int main() {
    S s1;
    const S s2;
    volatile S s3;
    const volatile S s4;
    
    s1.foo();
    s2.foo();
    s3.foo();
    s4.foo();
}