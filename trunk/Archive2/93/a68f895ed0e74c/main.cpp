#include <iostream>

struct foo
{
    foo()
    //    : foo(42)
    {
        this->foo::foo(42);
        std::cout << "foo()\n";
    }
    
    foo(int)
    {
        std::cout << "foo(int)\n";
    }
};

int main()
{
    foo f;
}