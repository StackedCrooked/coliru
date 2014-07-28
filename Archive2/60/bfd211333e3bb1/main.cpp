#include <iostream>

template<typename T> const T a = 0;

template<> const float a<float> = 5;
template<> const double a<double> = 14;
template<> const char a<char> = 65;
template<> const wchar_t a<wchar_t> = 66;

int main()
{
    std::cout << a<int> << std::endl;
    std::cout << a<float> << std::endl;
    std::cout << a<double> << std::endl;
    std::cout << a<char> << std::endl;
    std::wcout << a<wchar_t> << std::endl;
}
