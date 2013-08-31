#include <iostream>
 
class B;
 
struct A
{
    A() {} 
    A(const B& b) {std::cout << "Constructor called";}
};
 
struct B
{
    operator A() {std::cout << "conversion operator called\n"; return A();}
};
 
void someMethod(A a) {}
 
 
int main()
{
    someMethod(B());
}