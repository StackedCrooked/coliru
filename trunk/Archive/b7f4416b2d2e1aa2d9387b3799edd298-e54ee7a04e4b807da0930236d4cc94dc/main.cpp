#include <iostream>


#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;

        

namespace impl
{
    struct Wrap
    {
        template<typename T>
        Wrap(const T&) {}
    };  
        
    template<typename T> void hook_before(T&, Wrap) {  std::cout << "hook_before: not overridden" << std::endl; }    
    template<typename T> void hook_after(T&, Wrap) {  std::cout << "hook_after : not overridden" << std::endl; }    
        
    template<typename T>
    struct Foo
    {
        template<typename Dec>
        void bar(const Dec& d)
        {
            hook_before(static_cast<T&>(*this), d);
            do_bar();
            hook_after(static_cast<T&>(*this), d);
        }
        
        void do_bar()
        {
        }
    };   
}
     

namespace library
{
    using namespace impl;

    struct EthDec {};
    struct Eth : Foo<Eth> {};
    
    struct IPDec {};
    struct IP : Foo<IP> {};
}


// user code
namespace impl
{        
    using namespace library;
    
    void hook_before(Eth&, const EthDec&)
    {
        std::cout << "hook_before: overridden for Eth" << std::endl;
    }
    
    template<typename P, typename D>
    void hook_after(P&, const D&)
    {
        std::cout << "hook_after : overridden for T" << std::endl;
    }
}


int main()
{
    using namespace library;
    Eth eth;
    EthDec dec;
    eth.bar(dec);
    
    IP ip;
    IPDec ipdec;
    ip.bar(ipdec);
}