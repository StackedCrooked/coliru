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
struct Selector
{
    static constexpr auto foo = foo1;
};

template <>
struct Selector<false>
{
    static constexpr auto foo = foo2;
};
 
int main()
{
   Selector<true>::foo();
   Selector<false>::foo();
}
