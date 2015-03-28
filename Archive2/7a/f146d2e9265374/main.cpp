#include <iostream>
#include <initializer_list>
#include <type_traits>

int main()
{
    auto a = { 1, 2 } ;
    
    std::cout << std::boolalpha << std::is_same< decltype(a), std::initializer_list<int> >::value << '\n' ;
}
