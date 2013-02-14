#include <stdint.h>
#include <cassert>

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

constexpr EtherType operator++(EtherType eth)
{
    return eth == EtherType::ARP ? EtherType::IP  :
           eth == EtherType::IP  ? EtherType::IP6 :
           EtherType();
}

constexpr EtherType operator+(EtherType eth, unsigned n)
{
    return n == 0 ? eth :
           n == 1 ? ++eth :
           ++eth + (n - 1);
}

enum class IPNum : uint8_t
{
    ICMP = 1,
    TCP  = 6,
    UDP  = 17
};

int main()
{
    assert(EtherType::ARP + 1 == EtherType::IP);
    assert(EtherType::IP  + 1 == EtherType::IP6);
    assert(EtherType::IP6 + 1 == EtherType());
    
    assert(!"verify");
}

