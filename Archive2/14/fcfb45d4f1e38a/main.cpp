#include <type_traits>
#include <iostream>

template <typename T, typename Enable = void>
struct Widget;

template <typename T>
struct Widget<T, typename std::enable_if<std::is_integral<T>::value>::type>
{
    Widget() { std::cout << "is_integral<T>" << std::endl; }
};

template <typename T>
struct Widget<T, typename std::enable_if<std::is_floating_point<T>::value>::type>
{
    Widget() { std::cout << "is_floating_point<T>" << std::endl; }
};

int main()
{
    Widget<int>{};
    Widget<char>{};
    Widget<float>{};
    Widget<double>{};
}
