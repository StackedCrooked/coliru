#include <iostream>

static int bar = bar;

int main()
{
    int foo = foo;
    std::cout << "foo = " << foo << std::endl;
    std::cout << "bar = " << bar << std::endl;
}