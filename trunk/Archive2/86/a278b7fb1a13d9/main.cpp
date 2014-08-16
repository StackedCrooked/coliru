#include <iostream>

void foo(int i)
{
    std::cout << "foo(int): " << i << std::endl;
}

void foo(double d)
{
    std::cout << "foo(double): " << d << std::endl;
}

typedef void (*FooI)(int);

typedef void (*FooD)(double);

template <bool>
struct Selector
{
    static const FooI foo;
};

template <bool select>
const FooI Selector<select>::foo = ::foo;

template <>
struct Selector<false>
{
    static const FooD foo;
};

const FooD Selector<false>::foo = ::foo;
 
int main()
{
   Selector<true>::foo(2);
   Selector<false>::foo(3.14);
}
