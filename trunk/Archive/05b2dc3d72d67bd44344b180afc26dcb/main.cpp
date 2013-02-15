#include <stdint.h>
#include <cassert>
#include <iostream>

enum class Layer : unsigned
{
    Physical    = 1,
    Network     = 2,
    Internet    = 3,
    Transport   = 4,
    Application = 5
};

constexpr Layer begin(Layer) { return Layer::Physical; }
constexpr Layer end(Layer) { return Layer(); }

constexpr const char * to_string(Layer eth)
{
    return eth == Layer::Physical ? "Layer::Physical" :
           eth == Layer::Network ? "Layer::Network" :
           eth == Layer::Internet ? "Layer::Internet" :
           eth == Layer::Transport ? "Layer::Transport" :
           eth == Layer::Application ? "Layer::Application" :
           "Layer::?";
}

std::ostream & operator<<(std::ostream & os, Layer eth)
{
    return os << to_string(eth);
}

constexpr Layer operator++(const Layer & layer)
{
    return layer == Layer::Physical    ? Layer::Network     :
           layer == Layer::Network     ? Layer::Internet    :
           layer == Layer::Internet    ? Layer::Transport   :
           layer == Layer::Transport   ? Layer::Application :
           Layer();
}

Layer operator++(Layer & layer)
{
    return layer = ++const_cast<const Layer&>(layer);
}

constexpr Layer operator+(const Layer layer, unsigned n)
{
    return n == 0 ? layer : (++layer + (n - 1));
}

enum class EtherType : uint16_t
{
    ARP  = 0x0806,
    IP   = 0x0800,
    IP6  = 0x86DD
};

constexpr EtherType operator++(const EtherType & eth)
{
    return eth == EtherType::ARP ? EtherType::IP  :
           eth == EtherType::IP  ? EtherType::IP6 :
           EtherType();
}

EtherType operator++(EtherType & eth)
{
    return eth = ++const_cast<const EtherType&>(eth);
}

constexpr EtherType operator+(const EtherType eth, unsigned n)
{
    return n == 0 ? eth : (++eth + (n - 1));
}

constexpr EtherType begin(EtherType) { return EtherType::ARP; }
constexpr EtherType end(EtherType) { return EtherType(); }


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

enum PortNumber : uint16_t {};

template<Layer> struct ProtocolEnum;
template<> struct ProtocolEnum<Layer::Network>   { using type = EtherType;  };
template<> struct ProtocolEnum<Layer::Internet>  { using type = IPNum;      };
template<> struct ProtocolEnum<Layer::Transport> { using type = PortNumber; };

template<typename ProtocolEnumType> struct ProtocolLayer;
template<> struct ProtocolLayer<EtherType>  { static constexpr Layer value = Layer::Network; };
template<> struct ProtocolLayer<IPNum>      { static constexpr Layer value = Layer::Internet; };
template<> struct ProtocolLayer<PortNumber> { static constexpr Layer value = Layer::Transport; };

#include <type_traits>

template<typename T, typename U>
constexpr bool IsSame(T, U)
{
    return std::is_same<T, U>::value;
}

template<typename Enum>
constexpr Layer GetLayer(Enum)
{
    return IsSame(Enum(), EtherType()) ? Layer::Network :
           IsSame(Enum(), IPNum()) ? Layer::Internet :
           IsSame(Enum(), PortNumber()) ? Layer::Transport : Layer();
}

template<typename EnumType>
void loop(EnumType)
{
    unsigned limit = 10;
    for (auto i = begin(EnumType()), e = end(EnumType()); i != e && --limit; ++i)
    {
        std::cout << i << std::endl;
    }    
}

int main()
{
    static_assert(EtherType::ARP + 1 == EtherType::IP , "");
    static_assert(EtherType::IP  + 1 == EtherType::IP6, "");
    static_assert(EtherType::IP6 + 1 == EtherType()   , "");
    static_assert(EtherType()    + 1 == EtherType()   , "");
    
    static_assert(++EtherType::ARP == EtherType::IP , "");
    static_assert(++EtherType::IP  == EtherType::IP6, "");
    static_assert(++EtherType::IP6 == EtherType()   , "");
    
    loop(Layer());
    loop(EtherType());
}

