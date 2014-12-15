#include <iostream>
#include <type_traits>
#include <typeinfo>
 
int main() 
{
    typedef std::conditional<true, int, double>::type Type1;
    typedef std::conditional<false, int, double>::type Type2;
    typedef std::conditional<sizeof(int) >= sizeof(double), int, double>::type Type3;
 
    std::cout << typeid(Type1).name() << '\n';
    std::cout << typeid(Type2).name() << '\n';
    std::cout << typeid(Type3).name() << '\n';
}