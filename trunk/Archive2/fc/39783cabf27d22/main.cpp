#include <cstdlib>
#include <iostream>

int bar() { return rand(); }
int foo(int x = bar()) { return x; }

int main()
{
    std::cout << foo() << std::endl;
}