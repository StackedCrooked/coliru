#include <iostream>

class Tester {
    public:
    void test(const int & a) { std::cout << a << std::endl; }
};

class Foo {
    public:    
    static Tester tests;
};

Tester Foo::tests;

int main() {
    
    Foo Bar;
    Bar.tests.test(1);
    std::cout << "Done" << std::endl;
    return 0;
}

