#include <iostream>
#include <functional>

struct Base {};

struct Derived : public Base
{
    void evaluate(std::function<void(const Derived&)> callback) const
    {
        callback(*this);
    }
    
    int foo = 42;
};

int main()
{
   Derived d;
   
   d.evaluate([](const Derived& d){std::cout << d.foo << std::endl;});
}
