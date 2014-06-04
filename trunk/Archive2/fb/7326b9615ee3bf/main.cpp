#include <iostream>
#include <string>

struct Foo {
    Foo(int i) { std::cout << "int ctor" << std::endl; }
    Foo(std::string s) { std::cout << "std::string ctor" << std::endl; }
    Foo(const Foo&) { std::cout << "Copy ctor" << std::endl; }
    Foo(Foo&&) { std::cout << "Move ctor" << std::endl; }
    Foo& operator=(const Foo&) { std::cout << "Copy assignment" << std::endl; return *this; }
    Foo& operator=(Foo&&) { std::cout << "Move assignment" << std::endl; return *this; }
    void doSomething() { std::cout << "did something" << std::endl; }
};

int main() {
    bool condition = false;

    Foo&& f = condition ? Foo{5} : Foo{"test"};
    f.doSomething();
}