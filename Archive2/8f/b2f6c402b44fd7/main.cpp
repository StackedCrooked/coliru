#include <iostream>
#include <type_traits>
 
struct A {};
 
int f()
{
    return 1;
}
 
int main() 
{
    std::cout << std::boolalpha;
    std::cout << std::is_function<A>::value << '\n';
    std::cout << std::is_function<int(int)>::value << '\n';
    std::cout << std::is_function<decltype(f)>::value << '\n';
    std::cout << std::is_function<int>::value << '\n';
}