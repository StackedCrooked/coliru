#include <type_traits>
#include <iostream>

struct foo
{
    template<typename T, typename std::enable_if< std::is_integral<T>::value, int >::type = 0>
    foo(T) { std::cout << "integral\n"; }
    
    template<typename T, typename std::enable_if< std::is_floating_point<T>::value, int >::type = 0>
    foo(T) { std::cout << "floating point\n"; }
};

int main()
{
    foo(42);
    foo(4.2);
}