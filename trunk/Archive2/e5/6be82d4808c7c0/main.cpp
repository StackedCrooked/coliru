#include <iostream>
#include <random>
#include <cstdlib>
using namespace std;

class Base
{
public:
    virtual void Foo()
    {
        std::cout << __PRETTY_FUNCTION__ << '\n';
    }
    virtual void Bar()
    {
        std::cout << __PRETTY_FUNCTION__ << '\n';
    }
};

class Derived1 : public Base
{
public:
    void Foo()
    {
        std::cout << __PRETTY_FUNCTION__ << '\n';
    }
    
    void Bar()
    {
        std::cout << __PRETTY_FUNCTION__ << '\n';
    }
};
        
class Derived2 : public Base
{
public:
    void Foo()
    {
        std::cout << __PRETTY_FUNCTION__ << '\n';
    }
    
    void Bar()
    {
        std::cout << __PRETTY_FUNCTION__ << '\n';
    }
};

class OtherClass
{
public:
    Base* obj;
    void (Base::*method)();
    
    void Add( Base* _obj, void (Base::*_method)() )
    {
        obj = _obj;
        method = _method;
    }
    
    void Run()
    {
        (obj->*method)();
    }
};

int main()
{
    Derived1 d1;
    Derived2 d2;
    
    OtherClass other;
    
    other.Add( &d1, &Base::Foo );
    other.Run();
    
    other.Add( &d2, &Base::Bar);
    other.Run();
}