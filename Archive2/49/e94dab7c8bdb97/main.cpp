#include <iostream>
#include <type_traits>
 
class A {};
 
int main() 
{
    std::cout << std::boolalpha;
    std::cout << std::is_integral<A>::value << '\n';
    std::cout << std::is_integral<float>::value << '\n';
    std::cout << std::is_integral<int>::value << '\n';
}