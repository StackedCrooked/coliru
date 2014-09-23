#include <iostream>

struct Base {
    Base() { throw "Base throwing\n"; }
};

struct Derived : Base{
    Derived()
    try : Base()
    {}
    catch(char const* p)
    {
        std::cout << p;
    }
};

int main()
{
    try { Derived d; }catch(...){}
}