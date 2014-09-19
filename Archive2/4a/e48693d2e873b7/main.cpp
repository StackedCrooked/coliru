#include <array>
#include <cstddef>
#include <type_traits>
#include <iostream>

template <typename T, std::size_t N>
class MyClass {};

template <typename T>
struct ArraySize;

template <typename T, std::size_t N>
struct ArraySize<MyClass<T, N>> : std::integral_constant<std::size_t, N> {};

template <typename T>
void foo()
{
    std::cout << ArraySize<T>::value << std::endl;
}  

int main()
{
    using Tbis = int;
    
    foo<MyClass<Tbis, 10>>();
}
