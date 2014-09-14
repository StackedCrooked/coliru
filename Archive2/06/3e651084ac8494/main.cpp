#include <iostream>
#include <type_traits>

template <typename T>
auto compare(T n1, T n2)
    -> typename std::enable_if<std::is_integral<T>::value
                               || std::is_floating_point<T>::value
                             , T>::type
{
    return n1<n2;
}

int main()
{    
    std::cout <<compare(1, 2) << std::endl;
    std::cout <<compare(3.0, 4.0) << std::endl;
}
