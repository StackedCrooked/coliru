#include <functional>
#include <iostream>

struct foo
{
    std::function<void()> f;
    
    foo()
        : f([this]{ std::cout << (void*)this << "\n"; })
    {}
};

int main()
{
    foo x;
    x.f();
    
    foo y = x;
    y.f();
}