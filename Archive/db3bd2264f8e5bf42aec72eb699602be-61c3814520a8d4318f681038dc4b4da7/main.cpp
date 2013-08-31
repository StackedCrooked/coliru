#include <iostream>

struct Foo
{
    void m()
    {
        std::cout << 42;
    }
};

template<typename C>
struct Temp
{
    C *p;
    template<void (C::*f)()> void call()
    {
        (p->*f)();
    }
};

template<typename C>
Temp<C> bar(C* obj)
{
    return {obj};
}

int main() 
{
    Foo foo;
    bar(&foo).call<&Foo::m>();
}