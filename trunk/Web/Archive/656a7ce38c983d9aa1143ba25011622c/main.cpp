#include <iostream>
#include <type_traits>

template <bool C>
using EnableIf = typename std::enable_if<C>::type*;

template<typename T>
void foo(EnableIf<sizeof(T) % 2 == 0> = 0)
{
    std::cout << "even" << std::endl;
}

template<typename T>
void foo(EnableIf<sizeof(T) % 2 != 0> = 0)
{
    std::cout << "odd" << std::endl;
}

int main()
{
    foo<int >();
    foo<char>();
    foo<char>();
    foo<long>();
}