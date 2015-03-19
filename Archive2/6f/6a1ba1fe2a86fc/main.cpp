#include <iostream>

struct transaction
{
};

struct entity
{
    virtual ~entity() = default;
    
    virtual void qux() = 0; // This never needs to lock (e.g. works on immutable data)
    
    virtual void foo(transaction& t) = 0; // This function does not lock.
    
    virtual void foo() = 0; // This is a convenience function that creates a transaction
                            // (i.e. locks) and calls the overload above.

    virtual void bar(transaction& t) = 0; // This function does not lock.
    
    virtual void bar() = 0; // This is a convenience function that creates a transaction
                            // (i.e. locks) and calls the overload above.
    
    virtual void register_on_before_event_handler(/*...*/) = 0;
    
    virtual void register_on_after_event_handler(/*...*/) = 0;
    
    virtual void register_on_event_handler(/*...*/) = 0;
};

struct entity_impl : entity
{
    virtual void qux() override { std::cout << __func__ << std::endl; }
    
    virtual void foo(transaction& t) override { std::cout << __func__ << std::endl; }
    
    virtual void foo() override { std::cout << __func__ << std::endl; }

    virtual void bar(transaction& t) override { std::cout << __func__ << std::endl; }
    
    virtual void bar() override { std::cout << __func__ << std::endl; }
    
    virtual void register_on_before_event_handler() override { std::cout << __func__ << std::endl; }
    
    virtual void register_on_after_event_handler() override { std::cout << __func__ << std::endl; }
    
    virtual void register_on_event_handler() override { std::cout << __func__ << std::endl; }
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
    
    e.register_on_before_event_handler(/*...*/);
    e.register_on_after_event_handler(/*...*/);
    e.register_on_event_handler(/*...*/); 
}