#include <iostream>

namespace N
{
    struct A{ };
    
    void f(A const &) { std::cout << "N::f" << std::endl; }
}

template<typename T>
void f(T const &) { std::cout << "::f" << std::endl; }

int main()
{
    N::A a;
    
    N::f(a); //invoke N::f()  ......................................... (looks and intention agree)
    
    f(a);    //invoke ::f() ... but wait, looks could be deceptive! ... (looks and intention dont agree)
}