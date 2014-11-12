#include <iostream>


#define TRACE() std::cout << __LINE__ << " \t" << __PRETTY_FUNCTION__ << std::endl


namespace Stack {


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
    TRACE();
    pop(IPv4Decoder{});
}


void do_pop(const IPv4Decoder&, Default)
{
    TRACE();
}


} // namespace Stack


int main()
{
    using namespace Stack;
    pop(EthernetDecoder{});
}


namespace Stack
{
    // User hook for IPv4Decoder
    void do_pop(const IPv4Decoder&, Override)
    {
        TRACE();
    }
}
