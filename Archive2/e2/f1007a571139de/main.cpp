#include <iostream>

void foo(int i)
{
    std::cout << "foo(int): " << i << std::endl;
}

void foo(double d)
{
    std::cout << "foo(double): " << d << std::endl;
}

template <bool>
struct Selector
{
    static constexpr auto foo = static_cast<void(*)(int)>(::foo);
};

template <>
struct Selector<false>
{
    static constexpr auto foo = static_cast<void(*)(double)>(::foo);
};
 
int main()
{
   Selector<true>::foo(2);
   Selector<false>::foo(3.14);
}
