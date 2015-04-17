#include <iostream>
#include <type_traits>
 
class A {};
 
template <class T>
T f(T i)
{
    static_assert(std::is_integral<T>::value, "Integer required.");
    return i;
}

int main() 
{
    std::cout << std::boolalpha;
    std::cout << std::is_integral<A>::value << '\n';
    std::cout << std::is_integral<float>::value << '\n';
    std::cout << std::is_integral<int>::value << '\n';
    std::cout << f(123) << '\n';
    
    std::cout << "Test" << '\n';
}