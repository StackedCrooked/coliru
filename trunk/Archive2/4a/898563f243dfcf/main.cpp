#include <iostream>

template<class T>
    constexpr T pi = T(3.1415926535897932385);

int main()
{
    std::cout << pi<int> << '\n';
    std::cout << pi<float> << '\n';
    std::cout << pi<double> << '\n';
    std::cout << sizeof(pi<float>) << '\n';
    std::cout << sizeof(pi<double>) << '\n';
}