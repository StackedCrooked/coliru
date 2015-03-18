#include <iostream>

struct events
{
    virtual void register_handler() = 0;
};

struct thread_free
{
    virtual void thread_free_foo() = 0;
    
    virtual void thread_free_bar() = 0;
};

struct thread_safe
{
    virtual void thread_safe_foo() = 0;
    
    virtual void thread_safe_bar() = 0;
};

struct basic
{
    virtual events& get_events() = 0;  
    
    virtual thread_free& get_thread_free() = 0;  
    
    virtual thread_safe& get_thread_safe() = 0;
    
    virtual void qux() = 0;
};

struct impl : public basic, public events, public thread_free, public thread_safe
{

    virtual events& get_events() override { return *this; }
    
    virtual thread_free& get_thread_free() override { return *this; }
    
    virtual thread_safe& get_thread_safe() override { return *this; }
    
    virtual void register_handler() override { std::cout << __func__ << std::endl; }
    
    virtual void qux() override { std::cout << __func__ << std::endl; }

    virtual void thread_free_foo() override { std::cout << __func__ << std::endl; }
    
    virtual void thread_free_bar() override { std::cout << __func__ << std::endl; }
    
    virtual void thread_safe_foo() override { std::cout << __func__ << std::endl; }
    
    virtual void thread_safe_bar() override { std::cout << __func__ << std::endl; }
    
};

int main()
{
    impl i; 
    i.qux();
    
    i.get_thread_free().thread_free_foo();
    i.get_thread_free().thread_free_bar();
    
    i.get_thread_safe().thread_safe_foo();
    i.get_thread_safe().thread_safe_bar();
    
    i.get_events().register_handler();
}