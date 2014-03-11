#include <iostream>

struct Foo {
    Foo()
    {
        std::cout << '.';
        Foo(bar);
    }
};

int main()
{
    Foo f;
}