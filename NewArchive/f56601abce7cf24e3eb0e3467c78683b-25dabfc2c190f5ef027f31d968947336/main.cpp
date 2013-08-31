#include <type_traits>
#include <iostream>

template < typename T >
struct foo
{
    operator double() { return 0; }
    template < typename = typename std::enable_if<std::is_integral<T>{}>::type >
    operator int() { return 42; }
};

int main()
{
    foo<double> f;
    int i = f;
    std::cout << i;
}