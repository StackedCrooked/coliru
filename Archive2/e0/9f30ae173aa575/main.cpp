#include <iostream>

#define TRACE std::cout << __LINE__ << " \t" << __PRETTY_FUNCTION__ << std::endl;

namespace Stack
{
    struct Default  {};
    struct Override : Default {};

    template<typename T>
    void pop(const T& t)
    {
        do_pop(t, Override{});
    }

    struct EthernetDecoder {};
    struct IPv4Decoder {};

    void do_pop(const EthernetDecoder&, Default)
    {
        TRACE
        pop(IPv4Decoder{});
    }

    struct TCPDecoder {};

    void do_pop(const IPv4Decoder&, Default)
    {
        TRACE
        pop(TCPDecoder{});
    }

    void do_pop(const TCPDecoder&, Default)
    {
        TRACE
    }
}



int main()
{
    using namespace Stack;
    pop(EthernetDecoder{});
}



namespace Stack
{
    void do_pop(const EthernetDecoder& dec, Override)
    {
        TRACE
        do_pop(dec, Default());
    }

    void do_pop(const TCPDecoder& dec, Override)
    {
        TRACE
        do_pop(dec, Default());
    }
}
