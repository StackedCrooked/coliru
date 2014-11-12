#include <iostream>
#include <type_traits>
#include <array> 
struct A {
    int m;
};
 
struct B {
    B() {}
};
 
 
 
int main() 
{
    std::cout << std::boolalpha;
    std::cout << std::is_trivial<A>::value << '\n';
    std::cout << std::is_trivial<B>::value << '\n';
    
    typedef std::array<char, 3> ArrType;
    ArrType t={{}};
    std::cout << t[0] << " " << t[1] << " " << t[2] << std::endl;
    std::cout << std::is_trivial<ArrType>::value << std::endl;

    
}