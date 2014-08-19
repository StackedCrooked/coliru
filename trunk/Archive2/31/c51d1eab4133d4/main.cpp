#include <iostream>
#include <utility>

class Base
{
    public:
    
    Base() {}
    
    Base(Base&& b) { std::cout << "Move ctr"; }  
};

class Foo : public Base
{
    public:
    
    Foo(Base&& b, double otherArg) : Base(std::move(b))
    {
        /*ToDo - do something with otherArg*/
    }
};

int main()
{
    Foo(Base(), 2.0);
}