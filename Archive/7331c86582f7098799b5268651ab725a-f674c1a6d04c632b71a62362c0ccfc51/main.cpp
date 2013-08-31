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
    auto f = [](Base& b){b.Base::test();}; 
    f(d);
}
