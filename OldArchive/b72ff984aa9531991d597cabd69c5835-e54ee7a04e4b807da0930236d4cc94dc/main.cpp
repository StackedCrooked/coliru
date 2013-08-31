#include <iostream>


#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;

//
// User Header
//
namespace a
{
    namespace b
    {        
        template<typename Continuation, typename Decoder>
        void hook_pop(const Continuation& c, const Decoder& dec)
        {
            c(dec);
        }  
        
        template<typename Continuation, typename Decoder>
        void hook_push(const Continuation& c, const Decoder& dec)
        {
            c(dec);
        }        
    }
}


//
// Header
// 

namespace a
{    
    
    template<typename Continuation, typename Decoder>
    void hook_pop(const Continuation& c, const Decoder& dec)
    {
        c(dec);
    }
    
    template<typename Continuation, typename Decoder>
    void hook_push(const Continuation& c, const Decoder& dec)
    {
        c(dec);
    }
    
    namespace b
    {   
        template<typename CLP>
        struct BasicProtocol
        {
            template<typename Decoder>
            void pop(const Decoder& dec)
            {
                hook_pop([&](const Decoder& dec){ do_pop(dec); }, dec);
            }
            
            template<typename Decoder>
            void do_pop(const Decoder& dec)
            {
                TRACE
            }
            
            
            template<typename Decoder>
            void push(const Decoder& dec)
            {
                hook_push([&](const Decoder& dec){ do_push(dec); }, dec);
            }
            
            template<typename Decoder>
            void do_push(const Decoder& dec)
            {
                TRACE
            }
        };
        
        template<typename>
        struct Dec {};
        struct Eth : b::BasicProtocol<Eth> {};    
        struct IPv4 : b::BasicProtocol<IPv4> { };
        
        typedef b::Dec<Eth> EthDec;
        typedef b::Dec<IPv4> IPv4Dec;
    }
    
    using b::Eth;
    using b::EthDec;
    using b::IPv4;
    using b::IPv4Dec;
}









int main()
{
    a::Eth eth;
    a::EthDec dec;
    eth.pop(dec);
}