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
    Foo f;
    
    Foo* foo = new Foo1;
    int* tab = new int[1454];
    
    {
        std::unique_ptr<Base> f(new Foo1);
        f->foo();
        std::shared_ptr<Base> p = std::make_shared<Foo1>();
        std::shared_ptr<Base> k = p;
    }
    
    std::vector<double> k;
    std::vector<int>::const_iterator it = k.begin();
    auto it2 = k.begin();
    k.push_back(15);
    
    
    for (const auto& a : k) {
        
        
    }
    
    
    
    
    Foo1 foo1;
    Foo2 foo2;
    callFoo(&foo1);
    callFooFoo1(&foo1);
    callFoo(&foo2);
    
    
    return 0;
}
