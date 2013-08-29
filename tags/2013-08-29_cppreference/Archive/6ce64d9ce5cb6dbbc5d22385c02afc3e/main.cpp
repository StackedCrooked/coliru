#include <iostream>
#include <vector>


template<template<class, class...> class T, class ...U>
struct Test
{
    typedef T<U...> Type;
    
    
    Test()
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};


template<template<class, class...> class T, class ...U>
void fun(const T<U...> &)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}


int main()
{
    Test<std::vector, int>();
    Test<std::vector, int, std::allocator<int> >();
    
    fun(std::vector<int>());
    fun(std::vector<int, std::allocator<int> >());
}