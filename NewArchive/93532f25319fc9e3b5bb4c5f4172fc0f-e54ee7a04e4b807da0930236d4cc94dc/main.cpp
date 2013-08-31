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
    }
    
    using impl::Foo;
}


// user code
namespace library
{
    namespace impl
    {      
        template<typename T>
        void hook_after(T&)
        {
            std::cout << "special hook_after" << std::endl;
        }       
    }
}


int main()
{
    
    library::Foo<int> foo;
    foo.bar();
}