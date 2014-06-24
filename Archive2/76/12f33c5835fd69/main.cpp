#include <iostream>
#include <string>
#include <vector>
#include <type_traits>

struct A{int value;};

struct B{
    B(A &&value) : a(std::forward<A>(value)){}
    A&& a;
};
       
int main()
{
    // allowed
    B(A()).a;
    
    // error
    B b = B(A());
    b.a;
    
    return 0;
}
