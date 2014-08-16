#include <iostream>

void foo1()
{
    std::cout << "foo1" << std::endl;
}

void foo2()
{
    std::cout << "foo2" << std::endl;
}

typedef void (*Foo)();

template <bool>
struct Selector
{
    static const Foo foo;
};

template <bool select>
const Foo Selector<select>::foo = foo1;

template <>
const Foo Selector<false>::foo = foo2;
 
int main()
{
   Selector<true>::foo();
   Selector<false>::foo();
}
