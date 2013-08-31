#include <iostream>
#include <vector>

template<template<class, class...> class T, class ...U>
class Test
{
};


int main()
{
    Test<std::vector, int>(); // use default alloctor
    Test<std::vector, int, std::allocator<int> >(); // use default alloctor
    std::cout << "End of program." << std::endl;
}