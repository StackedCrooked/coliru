#include <iostream>
 
class A;
 
class B
{
    operator A() {std::cout << "conversion operator called\n"; return A();}
};
 
class A
{
public:
    A() {} 
    A(B b) {std::cout << "Constructor called";}
};
 
void someMethod(A a) {}
 
 
int main()
{
    someMethod(B());
}