#include <iostream>

int foo(int x)
{
    return x+1;
}

typedef decltype(foo)*fooptr_t;
fooptr_t fooptr = foo;

int main()
{
    std::cout << fooptr(41) << std::endl;
}
