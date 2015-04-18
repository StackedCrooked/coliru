#include <iostream>
#include <type_traits>
 
struct A {
    int m;
};
 
struct B {
    virtual void foo();
};
 
struct C {
    virtual void foo() = 0;
};
 
struct D : C {};
 
int main()
{
    float f = -0.0f;
    std::cout << std::boolalpha;
    std::cout << "int: " << (*(reinterpret_cast<unsigned int*>(&f))) << std::endl;
    std::cout << std::is_abstract<A>::value << '\n';
    std::cout << std::is_abstract<B>::value << '\n';
    std::cout << std::is_abstract<C>::value << '\n';
    std::cout << std::is_abstract<D>::value << '\n';
}