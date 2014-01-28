#include <iostream>
#include <type_traits>
#include <iterator>

void foo(std::size_t)
{
    std::cout << "foo(std::size_t)" << std::endl;
}

template<typename T, 
         typename std::iterator_traits<T>::value_type::type* = nullptr>
void foo(T)
{
    std::cout << "foo(T)" << std::endl;
}

int main()
{
    foo(42);
    
}