#include <iostream>
#include <type_traits>
 
class A {};
 
int main() 
{
    std::cout << 33;
    std::cout << std::is_floating_point<A>::value << '\n';
    std::cout << std::is_floating_point<float>::value << '\n';
    std::cout << std::is_floating_point<int>::value << '\n';
}