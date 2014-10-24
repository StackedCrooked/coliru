#include <iostream>
#include <string>
#include <vector>
#include <iterator>

class Base
{
public:  
    virtual ~Base() {}
    
    virtual void foo() const = 0;
    
    virtual void bar() const {
        std::cout << "BarBase\n";    
    }
};

class Foo1 : public Base
{
public:
    virtual void foo() const
    {
        std::cout << "Foo1\n";    
    }
    void bar() const {
        std::cout << "BarFoo1\n";    
    }
};


class FooFoo1 : public Foo1
{
public:
    void bar() const {
        std::cout << "BarFooFoo1\n";    
    }
};

class Foo2 : public Base
{
public:
    virtual void foo() const
    {
        std::cout << "Foo2\n";    
    }
    void bar() const {
        std::cout << "BarFoo2\n";    
    }
};


void callFoo(const Base* b)
{
    b->foo();  
    b->bar();
}

void callFooFoo1(const Foo1* b)
{
    b->foo();  
    b->bar();
}

int main()
{
    Foo1 foo1;
    Foo2 foo2;
    callFoo(&foo1);
    callFooFoo1(&foo1);
    callFoo(&foo2);
    
    
    return 0;
}
