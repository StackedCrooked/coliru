
#include <iostream>
#include <type_traits>

using IntType = unsigned long long;
template <IntType N> struct Int {};

template<typename T>
void f(T) { std::cout << "f(T)" << std::endl; }

template<IntType N>
void f(Int<N>) { std::cout << "f(Int<IntType>)" << std::endl; }

int main()
{
    f(Int<0>{});
}