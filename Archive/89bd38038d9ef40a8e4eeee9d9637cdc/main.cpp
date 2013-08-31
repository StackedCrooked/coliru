#include <stdint.h>
#include <cassert>
#include <iostream>

enum class Layer : int
{
    Physical    = 1,
    Network     = 2,
    Internet    = 3,
    Transport   = 4,
    Application = 5
};

constexpr Layer GetHigherLayer(Layer layer)
{
    return layer == Layer::Physical    ? Layer::Network   :
           layer == Layer::Network     ? Layer::Internet  :
           layer == Layer::Internet    ? Layer::Transport :
           Layer::Application;
}

enum class EtherType : uint16_t
{
    ARP  = 0x0806,
    IP   = 0x0800,
    IP6  = 0x86DD
};

constexpr EtherType operator++(EtherType & eth)
{
    return eth = (eth == EtherType::ARP ? EtherType::IP  :
                  eth == EtherType::IP  ? EtherType::IP6 :
                  EtherType());
}

constexpr EtherType operator+(EtherType eth, unsigned n)
{
    return n == 0 ? eth : (++eth + (n - 1));
}

constexpr EtherType begin(EtherType)
{
    return EtherType::ARP;
}

constexpr EtherType end(EtherType)
{
    return EtherType();
}

enum class IPNum : uint8_t
{
    ICMP = 1,
    TCP  = 6,
    UDP  = 17
};

constexpr const char * to_string(EtherType eth)
{
    return eth == EtherType::ARP ? "EtherType::ARP" :
           eth == EtherType::IP  ? "EtherType::IP"  :
           eth == EtherType::IP6 ? "EtherType::IP6" :
           "EtherType::?";
}

std::ostream & operator<<(std::ostream & os, EtherType eth)
{
    return os << to_string(eth);
}

int main()
{
    static_assert(EtherType::ARP + 1 == EtherType::IP , "");
    static_assert(EtherType::IP  + 1 == EtherType::IP6, "");
    static_assert(EtherType::IP6 + 1 == EtherType()   , "");
    
    static_assert(++EtherType::ARP == EtherType::IP , "");
    static_assert(++EtherType::IP  == EtherType::IP6, "");
    static_assert(++EtherType::IP6 == EtherType()   , "");
    
    unsigned limit = 10;
    for (auto i = begin(EtherType()), e = end(EtherType()); i != e && --limit; ++i)
    {
        std::cout << i << std::endl;
    }
}

