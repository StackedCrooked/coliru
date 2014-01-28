#include <iostream>
#include <type_traits>
 
int main()
{
    int i = 42;
    int& ref1 = i, ref2 = i;
    
    std::cout << std::is_lvalue_reference<decltype(ref1)>::value << '\n';
    std::cout << std::is_lvalue_reference<decltype(ref2)>::value << '\n';
}
