#include <iostream>

template<typename T> const int a = 0;

template<> const int a<float> = 5;
template<> const int a<double> = 14;
template<> const int a<char> = 65;
template<> const int a<wchar_t> = 66;

int main()
{
    std::cout << a<int> << std::endl;
    std::cout << a<float> << std::endl;
    std::cout << a<double> << std::endl;
    std::cout << a<char> << std::endl;
    std::cout << a<wchar_t> << std::endl;
}
