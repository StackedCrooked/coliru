#include <algorithm>
#include <iostream>
#include <cstdlib>

template<typename T, std::size_t N>
void foo(T const (&)[N])
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

template<typename T>
void foo(T const&)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main() 
{
    int arr1[10];
    foo(arr1);
    
    int arr2[0];
    foo(arr2);
}
