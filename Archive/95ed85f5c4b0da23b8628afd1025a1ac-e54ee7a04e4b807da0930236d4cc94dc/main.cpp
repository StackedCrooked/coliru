#include <iostream>


#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;

        

namespace library
{
    template<typename T> void hook_before(T&)
    { std::cout << "default hook_before" << std::endl; }
    
    template<typename T> void hook_after(T&)
    { std::cout << "default hook_after" << std::endl; }
    
    namespace impl
    {        
        template<typename T>
        struct Foo
        {
            void bar()
            {
                hook_before(*this);
                do_bar();
                hook_after(*this);
            }
            
            void do_bar()
            {
            }
        };
        
        struct Eth : Foo<Eth> {};
    }
    
}


// user code
namespace library
{    
    namespace impl
    {    
        void hook_after(library::impl::Eth&)
        {
            std::cout << "default hook_after" << std::endl;
        }        
    }
    
    using impl::hook_after;
}


int main()
{
    
    library::impl::Eth eth;
    eth.bar();
}