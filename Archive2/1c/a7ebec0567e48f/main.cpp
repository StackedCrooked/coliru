#include <iostream>
#include <memory>

template<int S>
struct A {
    A() { std::cout<<"A::A"<<std::endl; }    
    template<int S2>
    A(const A<S2>&) { std::cout<<"A::A&"<<std::endl; }
    template<int S2>
    A(const A<S2>&&) { std::cout<<"A::A&&"<<std::endl; }    
    ~A() { std::cout<<"~A::A"<<std::endl;}        
};
A<0> foo () {    
    A<2> a; A<1> b(a); A<0> c(b); return c;   // calls dtor/ctor 8 times
    //return A<0>(A<1>(A<2>()));  // calls dtor/ctor 10 times
}
int main()
{
   A<0> a=foo();
   return 0;
}