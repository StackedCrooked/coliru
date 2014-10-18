#include <type_traits>
#include <iostream>

// Bigger between two types
template<typename T1, typename T2> 
using Bigger = std::conditional_t<sizeof(T1) >= sizeof(T2), T1, T2>;

int main()
{
    std::cout << sizeof(double) << '\n';
    std::cout << sizeof(Bigger<int, Bigger<char, Bigger<long, Bigger<std::string, Bigger<long long, double>>>>>) << '\n';
}
