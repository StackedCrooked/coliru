#include <iostream>
#include <initializer_list>
#include <memory>

struct Base
{
    virtual ~Base()
    {
        std::cout << __PRETTY_FUNCTION__ << '\n';
    }
    
    virtual int GetValue() { return 0; }
};

struct Derived1 : public Base
{
    virtual ~Derived1()
    {
        std::cout << __PRETTY_FUNCTION__ << '\n';
    }
    
    int GetValue() override { return 1; }
};

struct Derived2 : public Base
{
    virtual ~Derived2()
    {
        std::cout << __PRETTY_FUNCTION__ << '\n';
    }
    
    int GetValue() override { return 2; }
};

int main()
{
    std::initializer_list< std::shared_ptr<Base> > foo
    {
        std::make_shared<Derived1>(),
        std::make_shared<Derived2>()
    };
    
    auto iter = std::begin(foo);
    (*iter)->GetValue(); // access violation
    
    return 0;
}