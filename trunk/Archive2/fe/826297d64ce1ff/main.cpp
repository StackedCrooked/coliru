#include <iostream>

class Foo {
    public:
    void foo();
};

void Foo::foo() {
    std::cout << "method\n";
}

void foo() {
    std::cout << "free function\n";
}

int main() {
    std::cout << "This is calling a method (a.k.a 'member function'): ";
    
    Foo f;
    f.foo();
    
    std::cout << "This is calling a free function: ";
    
    foo();
}
