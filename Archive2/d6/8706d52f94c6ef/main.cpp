#include <type_traits>

enum class X
{
    a = 1,
    b = 2,
    c = 3
};

template<typename T>
struct enum_proxy
{
    enum_proxy(T v) : value{v} { }
    
    explicit operator bool() { return static_cast<std::underlying_type_t<T>>(value) != 0; }
    
    operator T() { return value; }
    
    T value;
};

template<typename T>
bool is_non_zero(T x)
{
    return (static_cast<std::underlying_type_t<X>>(x) != 0);
}

enum_proxy<X> operator & (X lhs, X rhs)
{
    return X(static_cast<std::underlying_type_t<X>>(lhs) &
             static_cast<std::underlying_type_t<X>>(rhs));
}

#include <iostream>

int main()
{
    if ((X::a & X::c) & X::b) { std::cout << "Hi"; } else { std::cout << "Ho"; }
    if ((X::a & X::c) == X::b) { std::cout << "Hi"; } else { std::cout << "Ho"; }
    if ((X::a & X::c) < X::b) { std::cout << "Hi"; } else { std::cout << "Ho"; }
}