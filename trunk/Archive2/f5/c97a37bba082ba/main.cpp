#include <iostream>
#include <string>
#include <vector>

struct A {
 A(int);
 A(int, int);
};
A::A(int = 0) {}
class D: public A {};
D d; // implicitly-defined D() calls A(int)

int main()
{
    
}
