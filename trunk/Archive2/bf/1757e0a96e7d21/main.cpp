#include <iostream>

struct transaction
{
};

struct entity
{
    virtual void qux() = 0;
    
    virtual void foo(transaction& t) = 0;
    
    virtual void foo() = 0;

    virtual void bar(transaction& t) = 0;
    
    virtual void bar() = 0;
    
    virtual void register_handler() = 0;
};

struct entity_impl : entity
{
    virtual void qux() override { std::cout << __func__ << std::endl; }
    
    virtual void foo(transaction& t) override { std::cout << __func__ << std::endl; }
    
    virtual void foo() override { std::cout << __func__ << std::endl; }

    virtual void bar(transaction& t) override { std::cout << __func__ << std::endl; }
    
    virtual void bar() override { std::cout << __func__ << std::endl; }
    
    virtual void register_handler() override { std::cout << __func__ << std::endl; }
};

int main()
{
    entity_impl e; 
    e.qux();
 
    transaction t;
    e.foo(t);
    e.bar(t);
    
    e.foo();
    e.bar();
    
    e.register_handler();    
}