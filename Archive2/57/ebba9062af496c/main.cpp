#include <iostream>
#include <utility>
#include <functional>

class Parent
{
protected:
    Parent(std::function<double(double)> func)
    {
        std::cout << func(42);
    };
};

class Derived : public Parent
{
public:
    const double val;

    double MyFunc(double x)
    {
        return x / val;
    }

    Derived(double value)
        : Parent(std::bind(&Derived::MyFunc, this, std::placeholders::_1))
        , val(value)
    {}
};

int main()
{
    Derived d(2); // Broken because `val` is not initialised in the `Parent` ctor
}