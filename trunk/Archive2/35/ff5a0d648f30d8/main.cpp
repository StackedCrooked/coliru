#include <iostream>

struct transaction
{
};

struct entity
{
    struct events
    {
        virtual void register_on_before_event_handler(/*...*/) = 0;
        
        virtual void register_on_after_event_handler(/*...*/) = 0;
        
        virtual void register_on_event_handler(/*...*/) = 0;
    };
    
    struct thread_free
    {
        virtual void foo(transaction&) = 0;
        
        virtual void bar(transaction&) = 0;
    };
    
    struct thread_safe
    {
        virtual void foo() = 0;
        
        virtual void bar() = 0;
    };

    virtual events& get_events() = 0;  
    
    virtual thread_free& get_thread_free() = 0;  
    
    virtual thread_safe& get_thread_safe() = 0;
    
    virtual void qux() = 0;
};

struct entity_impl : public entity
                   , public entity::events
                   , public entity::thread_free
                   , public entity::thread_safe
{

    virtual entity::events& get_events() override { return *this; }
    
    virtual entity::thread_free& get_thread_free() override { return *this; }
    
    virtual entity::thread_safe& get_thread_safe() override { return *this; }
    
    virtual void register_on_before_event_handler() { std::cout << __func__ << std::endl; }
    
    virtual void register_on_after_event_handler() { std::cout << __func__ << std::endl; }
    
    virtual void register_on_event_handler() { std::cout << __func__ << std::endl; }
    
    virtual void qux() override { std::cout << __func__ << std::endl; }

    virtual void foo(transaction&) override { std::cout << __func__ << std::endl; }
    
    virtual void bar(transaction&) override { std::cout << __func__ << std::endl; }
    
    virtual void foo() override { std::cout << __func__ << std::endl; }
    
    virtual void bar() override { std::cout << __func__ << std::endl; }
    
};

int main()
{
    entity_impl e; 
    e.qux();
 
    transaction t;
    e.get_thread_free().foo(t);
    e.get_thread_free().bar(t);
    
    e.get_thread_safe().foo();
    e.get_thread_safe().bar();
    
    e.get_events().register_on_before_event_handler(/*...*/);
    e.get_events().register_on_after_event_handler(/*...*/);
    e.get_events().register_on_event_handler(/*...*/);
}