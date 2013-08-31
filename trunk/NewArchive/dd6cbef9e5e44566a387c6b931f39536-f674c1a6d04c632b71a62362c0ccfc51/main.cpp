#include <iostream>

class A;

class B
{
    operator A() {return A();}
};

class A
{
public:
    A() {std::cout << "Convertion operator called";}

    A(B b) {std::cout << "Constructor called";}
};

void someMethod(A a)
{
    
}


int main()
{
    someMethod(B());
}
