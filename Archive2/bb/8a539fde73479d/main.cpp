#include <iostream>

class X
{
};

class Y : public X
{
};

class A 
{ 
    public:
        virtual void foo(X* xptr) = 0; 
};

class B : public A
{
    public:
        void foo(X* xptr) 
        { 
            std::cout << "bar" << std::endl; 
        }
};
    

int main()
{
    Y y_instance;
    B b_instance;
    
    b_instance.foo( &y_instance );
    return 0;
}
