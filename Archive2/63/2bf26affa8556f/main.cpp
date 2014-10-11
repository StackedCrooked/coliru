#include <array>
#include <cstddef>

enum class EtherType { ARP, VLAN, IPv4, IPv6 };
enum class IPProtNum { TCP, UDP, ICMP };
enum class IPv6NextHeader { TCP, UDP, ICMP };

struct EthernetHeader
{
    EtherType getEtherType() const;
};

struct VLANHeader
{
    static VLANHeader& create_from(EthernetHeader&);
    EtherType getEtherType() const;
};

struct ARPHeader
{
    static ARPHeader& create_from(EthernetHeader&);
    static ARPHeader& create_from(VLANHeader&);
};

struct IPv4Header
{
    static IPv4Header& create_from(EthernetHeader&);
    static IPv4Header& create_from(VLANHeader&);
    IPProtNum getProtocol() const;
};

struct IPv6Header
{
    static IPv6Header& create_from(EthernetHeader&);
    static IPv6Header& create_from(VLANHeader&);
    IPv6NextHeader getNextHeader() const;
};

struct TCPHeader
{
    static TCPHeader& create_from(IPv6Header&);
    static TCPHeader& create_from(IPv4Header&);
};

struct UDPHeader
{
    static UDPHeader& create_from(IPv6Header&);
    static UDPHeader& create_from(IPv4Header&);
};

struct ICMPv4Header
{
    static ICMPv4Header& create_from(IPv4Header&);
};

struct ICMPv6Header
{
    static ICMPv6Header& create_from(IPv6Header&);
};

template<typename ...Args>
struct Signature { typedef void(*type)(Args&...); };

template<typename...>
struct Route;

template<> struct Route<TCPHeader, IPv4Header, EthernetHeader> { enum { id = 0 }; };
template<> struct Route<TCPHeader, IPv6Header, EthernetHeader> { enum { id = 1 }; };
template<> struct Route<UDPHeader, IPv4Header, EthernetHeader> { enum { id = 3 }; };
template<> struct Route<UDPHeader, IPv6Header, EthernetHeader> { enum { id = 4 }; };

template<> struct Route<TCPHeader, IPv4Header, VLANHeader, EthernetHeader> { enum { id = 5 }; };
template<> struct Route<TCPHeader, IPv6Header, VLANHeader, EthernetHeader> { enum { id = 6 }; };
template<> struct Route<UDPHeader, IPv4Header, VLANHeader, EthernetHeader> { enum { id = 7 }; };
template<> struct Route<UDPHeader, IPv6Header, VLANHeader, EthernetHeader> { enum { id = 8 }; };

template<> struct Route<ICMPv4Header, IPv4Header, EthernetHeader> { enum { id = 9 }; };
template<> struct Route<ICMPv6Header, IPv6Header, EthernetHeader> { enum { id = 10 }; };

template<> struct Route<ICMPv4Header, IPv4Header, VLANHeader, EthernetHeader> { enum { id = 11 }; };
template<> struct Route<ICMPv6Header, IPv6Header, VLANHeader, EthernetHeader> { enum { id = 12 }; };


template<> struct Route<ARPHeader, EthernetHeader> { enum { id = 13 }; };
template<> struct Route<ARPHeader, VLANHeader, EthernetHeader> { enum { id = 14 }; };


struct Stack
{
    Stack() : mLookup() {}
    
    template<typename ...Args>
    void register_pop_function(void (*fptr)(Args&...))
    {
        enum { index = Route<Args...>::id };
        mLookup[index] = reinterpret_cast<void(*)()>(fptr);
    }
    
    typedef void (*VoidFPtr)();
    std::array<VoidFPtr, 15> mLookup;
};


// pop to stack
template<typename ...Args>
void pop(Stack& stack, Args& ...args) {
    
    // get the index for this combination
    auto index = Route<Args...>::id;
    
    // get the function pointer 
    auto void_fptr = stack.mLookup[index];
    
    // if not registered then we drop packet
    if (!void_fptr)
    {
        return;
    }
    
    // obtain the signature for the function
    using RealFPtr = typename Signature<Args...>::type;
    
    // cast void function pointer to its real function pointer type
    auto real_fptr = reinterpret_cast<RealFPtr>(void_fptr);
    
    // call it with the arguments
    real_fptr(args...);
}


// IPv4 pop
template<typename ...Tail>
void handle(Stack& stack, IPv4Header& ipv4, Tail& ...tail) {
    switch (ipv4.getProtocol()) {
        case IPProtNum::TCP : pop(stack, TCPHeader::create_from(ipv4), ipv4, tail...); break;
        case IPProtNum::UDP : pop(stack, UDPHeader::create_from(ipv4), ipv4, tail...); break;
        case IPProtNum::ICMP: pop(stack, ICMPv4Header::create_from(ipv4), ipv4, tail...); break;
    }
}

// IPv6 pop
template<typename ...Tail>
void handle(Stack& stack, IPv6Header& ipv6, Tail& ...tail) {
    switch (ipv6.getNextHeader()) {
        case IPv6NextHeader::TCP : pop(stack, TCPHeader::create_from(ipv6), ipv6, tail...); break;
        case IPv6NextHeader::UDP : pop(stack, UDPHeader::create_from(ipv6), ipv6, tail...); break;
        case IPv6NextHeader::ICMP: pop(stack, ICMPv6Header::create_from(ipv6), ipv6,  tail...); break;
    }
}

// VLAN pop
template<typename ...Tail>
void handle(Stack& stack, VLANHeader& vlan, Tail& ...tail) {
    switch (vlan.getEtherType()) {
        case EtherType::ARP : pop(stack, ARPHeader::create_from(vlan), vlan, tail...); break;
        case EtherType::IPv4: handle(stack, IPv4Header::create_from(vlan), vlan, tail...); break;
        case EtherType::IPv6: handle(stack, IPv6Header::create_from(vlan), vlan, tail...); break;
        case EtherType::VLAN: break; // only one vlan tag allowed
    }
}


// Ethernet pop
void handle(Stack& stack, EthernetHeader& eth) {
    switch (eth.getEtherType()) {
        case EtherType::ARP : pop(stack, ARPHeader::create_from(eth), eth); break;
        case EtherType::IPv4: handle(stack, IPv4Header::create_from(eth), eth); break;
        case EtherType::IPv6: handle(stack, IPv6Header::create_from(eth), eth); break;
        case EtherType::VLAN: handle(stack, VLANHeader::create_from(eth), eth); break;
    }
}


int main()
{
    
    Stack stack;
    
    // note: the plus sign converts the lambda to a function pointer. E.g. `+[]{}` becomes void(*)()
    
    stack.register_pop_function(+[](ICMPv4Header& icmp, IPv4Header& ipv4, EthernetHeader& eth) {/**
        // Replying to an ICMP is like a stateless function call. No need to create a session object.
        Packet packet;
        packet.push_front(flip_header(icmp));
        packet.push_front(flip_header(ipv4));
        packet.push_front(flip_header(eth));
        stack.push(packet);
    */});
    
    stack.register_pop_function(+[](ARPHeader& arp, EthernetHeader& eth) {/**
        // ARP reply stateless
        if (arp.is_request()) {
            Packet packet;
            arp.target_hardware_address = stack.getLocalMAC();
            packet.push_front(flip_header(arp));
            packet.push_front(flip_header(eth));
            stack.push(packet);
        } else {
            // ...
        }
    */});
    
    stack.register_pop_function(+[](TCPHeader& tcp, IPv4Header& ipv4, EthernetHeader& eth) {/**
        // Establish connection or pop to existing connection.
    */});
    
    
    // - Even though there are many combinations only a few need to be registered.
    // - DHCP can also be handled like this because it used a fixed port numbers (67 for server and 68 for client).
    // - HTTP is not part of stack. It's simply the app that uses the TCP connection.
    // - 
    
    
    
    EthernetHeader fake_ethernet_header;
    handle(stack, fake_ethernet_header);
}




