#include <iostream>
#include <type_traits>
 
class A { int c; };
 
int main() 
{
    std::cout << std::boolalpha;
    std::cout << std::is_pointer<A>::value << '\n';
    std::cout << std::is_pointer<A*>::value << '\n';
    std::cout << std::is_pointer<float>::value << '\n';
    std::cout << std::is_pointer<int>::value << '\n';
    std::cout << std::is_pointer<int*>::value << '\n';
    std::cout << std::is_pointer<int**>::value << '\n';
}