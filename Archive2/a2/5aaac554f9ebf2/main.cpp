#include <type_traits>
#include <iostream>

template <typename... Ts>
using void_t = void;

template <typename T> struct is_int {}; 
template <> struct is_int<int> : std::true_type {};
template <typename T> using requires_integer = typename is_int<T>::type;

template <typename T, typename Enable = void>
struct Widget
{    
    Widget() { std::cout << "T is something else" << std::endl; }
};

template <typename T>
struct Widget<T, void_t<requires_integer<T>>>
{
    Widget() { std::cout << "T is int" << std::endl; }
};

int main()
{
    Widget<int>{};
    Widget<float>{};
}
