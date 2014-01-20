#include <utility>
#include <iostream>

struct SimpleClass
{    
    SimpleClass()
    {
        std::cout << "In constructor: " << this << std::endl;
    }

    ~SimpleClass()
    {
        std::cout  << "In destructor: " << this << std::endl;
    }
};

void DefArgFunc(SimpleClass x = {})
{
        std::cout << "In DefArgFunc: " << &x << std::endl;
}

int main()
{
    DefArgFunc();
    return 0;
}