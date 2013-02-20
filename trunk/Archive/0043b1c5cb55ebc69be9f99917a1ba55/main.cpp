#include <array>
#include <iostream>
#include <type_traits>

template<typename T>
auto constexpr get_element(T && t) -> typename std::remove_reference<decltype(t[0])>::type
{
    return typename std::remove_reference<decltype(t[0])>::type{};
}

template<typename T>
int constexpr get_length(T && t)
{
    return sizeof(typename std::remove_reference<T>::type)/sizeof(get_element(t));
}

template<typename T>
int constexpr get(T && t)
{
    return std::array<decltype(get_element(t)), get_length(t)>{};
}

template<typename T>
void print_signature(T&&)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main()
{
    print_signature(get_element("abc"));
    print_signature(get_length("abc"));
    
    std::cout << get_length("abc") << std::endl;
}