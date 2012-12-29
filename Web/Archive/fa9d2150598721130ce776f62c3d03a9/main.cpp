#include <iostream>
#include <type_traits>

    

template<typename T>
void foo(typename std::enable_if<sizeof(T) % 2 == 0>::type* = 0)
{
}


template<typename T>
void foo(typename std::enable_if<sizeof(T) % 2 == 1>::type* = 0)
{
}


int main()
{
    foo<int>();
    foo<char>();
}