#include <iostream>
#include <type_traits>

    

template<typename T, typename = typename std::enable_if<sizeof(T) % 2 == 0>::type>
void foo()
{
}


template<typename T, typename = typename std::enable_if<sizeof(T) % 2 == 1>::type>
void foo()
{
}


int main()
{
    foo<int>();
    foo<char>();
}