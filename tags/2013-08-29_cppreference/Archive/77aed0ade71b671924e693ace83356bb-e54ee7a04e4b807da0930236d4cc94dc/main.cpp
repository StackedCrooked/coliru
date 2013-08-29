#include <iostream>


#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;

        

namespace library
{
    template<typename T> void hook_before(T&, long = 0)
    { std::cout << "default hook_before" << std::endl; }
    
    template<typename T> void hook_after(T&, long = 0)
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
namespace user
{      
    struct Item {};
    
    void hook_after(library::Foo<Item>&)
    {
        std::cout << "special hook_after" << std::endl;
    }
}


int main()
{
    
    library::Foo<user::Item> foo;
    foo.bar();
}