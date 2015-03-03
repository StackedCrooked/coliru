#include <iostream>

class A {
    public :
    virtual ~A()
    {
        std::cout<<"destroying A"<<std::endl;
    }
};

class B : public A
{
};

class C : public B
{
};


int main()
{
    B b;
    C c;
    return 0;
}