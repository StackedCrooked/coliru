#include <type_traits>
#include <iostream>

struct base
{
    template<typename T, typename std::enable_if< std::is_integral<T>::value, int >::type = 0>
    base(T) { std::cout << "integral\n"; }
    
    template<typename T, typename std::enable_if< std::is_floating_point<T>::value, int >::type = 0>
    base(T) { std::cout << "floating point\n"; }
};

struct derived : base
{
    using base::base;
};

int main()
{
    derived{42};
    derived{4.2};
}