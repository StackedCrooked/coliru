#include <iostream>
#include <string>

struct Foo {
    Foo(){}
    Foo (std::string x) { std::cout << x << std::endl; }
    void test(){ std::cout << "test" << std::endl; };
};

std::string x("hello, world");

int main () { Foo(x); x.test(); }