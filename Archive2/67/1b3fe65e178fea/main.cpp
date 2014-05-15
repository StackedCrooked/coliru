#include <iostream>
#include <type_traits>
 
int main() 
{
    std::cout << std::boolalpha;
    std::cout << std::is_const<int>::value << '\n';
    std::cout << std::is_const<const int>::value  << '\n';
}