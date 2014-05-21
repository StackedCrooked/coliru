#include <iostream>

#define TRACE std::cout << __LINE__ << " \t" << __PRETTY_FUNCTION__ << std::endl;


namespace Stack
{
    template<typename T> struct Decoder {};


    template<typename T>
    void pop(const T& t)
    {
        do_pop(t);
    }


    struct EthernetDecoder : Decoder<EthernetDecoder> {};
    struct IPv4Decoder : Decoder<IPv4Decoder> {};


    void do_pop(const Decoder<EthernetDecoder>&)
    {
        TRACE
    }


    void do_pop(const Decoder<IPv4Decoder>&)
    {
        TRACE
    }

}



int main()
{
    using namespace Stack;
    pop(EthernetDecoder{});
    pop(IPv4Decoder{});
}



namespace Stack
{

    void do_pop(const EthernetDecoder&)
    {
        TRACE
    }

}
