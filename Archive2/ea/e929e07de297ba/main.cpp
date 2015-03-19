#include <type_traits>
#include <iostream>

template< class T >
constexpr T&& forward( typename std::remove_reference<T>::type& t )
{
    std::cout << __PRETTY_FUNCTION__ << '\n';
    return static_cast<T&&>(t);
}

template< class T >
constexpr T&& forward( typename std::remove_reference<T>::type&& t )
{
    std::cout << __PRETTY_FUNCTION__ << '\n';
    return static_cast<T&&>(t);
}

void g(int&)
{
    std::cout << __PRETTY_FUNCTION__ << '\n';
}

void g(int&&)
{
    std::cout << __PRETTY_FUNCTION__ << '\n';
}

template<class T>
void f(T&& x)
{ g(forward<T>(x)); }

int main()
{
    f(0);
    
    int x = 0;
    f(x);
}
