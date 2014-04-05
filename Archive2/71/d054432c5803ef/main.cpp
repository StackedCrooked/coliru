#include <iostream>

class X
{
};

class Y : public X
{
};

class A 
{ 
    virtual void foo(X x) = 0; 
};

class B : public A
{ 
    void foo(Y y) 
    { 
        std::cout << "bar" << std::endl; 
    }
};
    

int main()
{
    Y y_instance;
    B b_instance;
    
    b_instance.foo( y_instance );
    return 0;
}
