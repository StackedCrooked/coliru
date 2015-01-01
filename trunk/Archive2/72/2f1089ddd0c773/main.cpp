#include <iostream>
#include <memory>
#include <map>
#include <typeindex>
#include <string>




inline namespace Tags {
    
enum L1Tag { l1_tag };
enum EthTag { eth_tag };
enum VLANTag { vlan_tag };
enum IPv4Tag { ipv4_tag };
enum IPv6Tag { ipv6_tag };
enum UDPTag { udp_tag };
enum TCPTag { tcp_tag };
enum DHCPTag { dhcp_tag };
enum L5Tag { l5_tag };


template<typename ...T>
struct TypeList
{
    using type = TypeList<T...>;
};


template<typename ...T>
struct Append
{
    using type = TypeList<T...>;
};


template<typename A, typename B>
auto operator|(A, B)
{
    return typename Append<A, B>::type();
}

} // namespace Tags


struct Ethernet {};
struct IPv4 {};
struct IPv6 {};
struct TCP {};
struct UDP {};


template<typename>
struct Traits;


template<>
struct Traits<EthTag>
{
    using tag_type = EthTag;
    tag_type tag_value = tag_type();
    using protocol_type = Ethernet;
    using hlp_list = decltype(vlan_tag | ipv4_tag | ipv6_tag);
    using llp_list = decltype(l1_tag);
};


template<>
struct Traits<IPv4Tag>
{
    using tag_type = IPv4Tag;
    tag_type tag_value = tag_type();
    using protocol_type = IPv4;
    using hlp_list = decltype(tcp_tag | udp_tag);
    using llp_list = decltype(eth_tag | vlan_tag);
    
    template<typename LLP>
    using connect_type = decltype(LLP::tag_value | tag_value);
    
    template<typename LLP>
    static connect_type<LLP> connect_value()
    {
        return connect_type<LLP>();
    }
};


template<>
struct Traits<IPv6Tag>
{
    using tag_type = IPv6Tag;
    tag_type tag_value = tag_type();
    using protocol_type = IPv6;
    using hlp_list = decltype(tcp_tag | udp_tag);
    using llp_list = decltype(eth_tag | vlan_tag);
    
    template<typename LLP>
    using connect_type = decltype(LLP::tag_value | tag_value);
    
    template<typename LLP>
    static connect_type<LLP> connect_value()
    {
        return connect_type<LLP>();
    }
};


template<>
struct Traits<TCPTag>
{
    using tag_type = TCPTag;
    tag_type tag_value = tag_type();
    using protocol_type = TCP;
    using hlp_list = decltype(l5_tag);
    using llp_list = decltype(ipv4_tag | ipv6_tag);
    
    template<typename LLP>
    using connect_type = decltype(LLP::tag_value | tag_value);
    
    template<typename LLP>
    static connect_type<LLP> connect_value()
    {
        return connect_type<LLP>();
    }
};


template<typename T>
void print_type(T&&)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}


int main()
{
    using paths = decltype(
          (eth_tag | ipv4_tag | tcp_tag)
        | (eth_tag | ipv4_tag | udp_tag)
        | (eth_tag | ipv6_tag | tcp_tag)
        | (eth_tag | ipv6_tag | udp_tag)
    );
    
    
    print_type(paths());
    
    
}


