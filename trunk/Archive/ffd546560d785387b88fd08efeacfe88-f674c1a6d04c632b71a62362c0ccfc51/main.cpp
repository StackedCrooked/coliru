#include <functional>
#include <iostream>
#include <string>
#include <vector>


#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;


struct Base
{
    virtual void test()
    {
        TRACE
    }
};


struct Derived : Base
{
    virtual void test()
    {
        TRACE
    }
};


template<typename T>
void print_type(T)
{
    TRACE
}


int main()
{
    Derived d;
    
    d.Base::test(); // calls Derived::test, but what if I really want to call Base::test?
}
