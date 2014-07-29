#include <iostream>

struct Foo
{
    int i;
};

Foo& operator=(Foo& a, const Foo&b)
{
    a.i = b.i;
}

int main()
{
    Foo x = { 2 };
    Foo y = { 3 };
    
    x = y;
    std::cout << x.i << std::endl;
    
    x = x;
    std::cout << x.i << std::endl;
    
    return 0;
}