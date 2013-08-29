#include <iostream>

int foo()
{
    std::cout << "Hello World!";
    return 42;
}

auto bar = foo();

int main() {}
