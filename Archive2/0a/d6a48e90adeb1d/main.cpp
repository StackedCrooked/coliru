
#include <iostream>
#include <type_traits>

using IntType = unsigned long long;
template <IntType N> struct Int {};

template<typename T>
void f(T) { std::cout << "f(T)" << std::endl; }

template<long long N>
void f(Int<N>) { std::cout << "f(Int<long long>)" << std::endl; }

int main()
{
    f(Int<0>{});
}