#include <iostream>

void foo1()
{
    std::cout << "foo1" << std::endl;
}

void foo2()
{
    std::cout << "foo2" << std::endl;
}

template <bool>
constexpr auto foo = nullptr;

template <>
constexpr auto foo<true> = foo1;

template <>
constexpr auto foo<false> = foo2;
 
int main()
{
   foo<true>();
   foo<false>();
}