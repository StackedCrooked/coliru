#include <iostream>
#include <string>

struct Foo {
    Foo (std::string x) { std::cout << x << std::endl; }
};

std::string x("hello, world");

int main () { Foo{x}; }