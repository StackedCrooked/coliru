#include <iostream>
#include <type_traits>
 
struct A {};
 
struct B {
    int m;
};
 
struct C {
    virtual ~C();
};
 
int main()
{
    std::cout << std::boolalpha;
    std::cout << std::is_empty<A>::value << '\n';
    std::cout << std::is_empty<B>::value << '\n';
    std::cout << std::is_empty<C>::value << '\n';
}