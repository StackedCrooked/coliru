#include <array>
#include <cstddef>
#include <iostream>

template <typename T>
struct ArraySize;

template <typename T, std::size_t N>
struct ArraySize<std::array<T, N>> : std::integral_constant<std::size_t, N> {};

template <typename T>
void foo()
{
    std::cout << ArraySize<T>::value << std::endl;
}    

int main()
{
    foo<std::array<int, 10>>();
}
