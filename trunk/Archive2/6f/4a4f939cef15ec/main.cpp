#include <iostream>
#include <type_traits>
 
int main() 
{
    class A {};
    class B : public A {};
    class C {};
 
    bool b2a = std::is_convertible<B*, A*>::value;
    bool a2b = std::is_convertible<A*, B*>::value;
    bool b2c = std::is_convertible<B*, C*>::value;
 
    std::cout << std::boolalpha;
    std::cout << b2a << '\n';
    std::cout << a2b << '\n';
    std::cout << b2c << '\n';
}