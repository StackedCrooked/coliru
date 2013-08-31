#include <iostream>
#include <type_traits>

template<typename T>
void foo(typename std::enable_if<sizeof(T)%2 == 0>::type* = 0)
{
    std::cout << "even" << std::endl;
}

template<typename T>
void foo(typename std::enable_if<sizeof(T)%2 != 0>::type* = 0)
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