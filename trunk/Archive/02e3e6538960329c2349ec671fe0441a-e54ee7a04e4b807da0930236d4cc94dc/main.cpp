#include <iostream>


#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;

        

namespace library
{
    template<typename T> void hook_before(T&, long)
    { std::cout << "default hook_before" << std::endl; }
    
    template<typename T> void hook_after(T&, long)
    { std::cout << "default hook_after" << std::endl; }
    
    namespace impl
    {        
        template<typename T>
        struct Foo
        {
            void bar()
            {
                hook_before(*this, 0);
                do_bar();
                hook_after(*this, 0);
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
    
    void hook_after(library::Foo<Item>&, int)
    {
        std::cout << "special hook_after" << std::endl;
    }
}


int main()
{
    
    library::Foo<user::Item> foo;
    foo.bar();
}