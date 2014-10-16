#include <array>
#include <cstddef>

enum class EtherType { ARP, VLAN, IPv4, IPv6 };
enum class IPProtNum { TCP, UDP, ICMP };
enum class IPv6NextHeader { TCP, UDP, ICMP };


//
// Dummy header classes (analog to current stack)
//
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



//
// A route is the list of protocol headers that a packet will be composed of.
// For example: Ethernet->IPv4->ICMP or Ethernet->VLAN->IPv4->ICMP
//
template<typename...>
struct Route;


//
// Template specialization for all possible routes.
// Each route gets a unique numeric id.
//
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



//
struct Stack
{
    Stack() : mLookup() {}
        
    typedef void (*VoidFPtr)();
        
  
    // Register a route with a function pointer
    // E.g: void(*)(TCPHeader&, IPv4Header&, EthernetHeader&)
    template<typename ...Args>
    void register_route(void (*fptr)(Args&...))
    {
        // The route id is used as array index.
        enum { index = Route<Args...>::id };
        
        mLookup[index] = reinterpret_cast<VoidFPtr>(fptr);
    }
    
    // Array of function pointers. One for each route.
    // The index corresponds with the Route id.
    std::array<VoidFPtr, 15> mLookup;
};


// pop to stack
template<typename ...Args>
void pop(Stack& stack, Args& ...args) {
    
    
    // get the index for this combination
    auto index = Route<Args...>::id;
    
    // get the function pointer from the array 
    auto void_fptr = stack.mLookup[index];
    
    // if not registered then we drop packet
    if (!void_fptr)
    {
        return;
    }
    
    // make a typedef for the function pointer
    typedef void (*RealFPtr)(Args&...);
    
    // cast void function pointer to its real function pointer type
    auto real_fptr = reinterpret_cast<RealFPtr>(void_fptr);
    
    // call it with the arguments
    real_fptr(args...);
}


//
// Pop functions.
//
// - Each pop function has knowledge of higher layer protocol (via the protocol id like EtherType, IPProtnum)
// - The lower layer protocols are anonymously passed as templates in the `Tail...` parameter.
// - This is stateless. So no lock on the stack required here.
//

// => IPv4 pop
template<typename ...Tail>
void pop(Stack& stack, IPv4Header& ipv4, Tail& ...tail) {
    switch (ipv4.getProtocol()) {
        case IPProtNum::TCP : pop(stack, TCPHeader::create_from(ipv4), ipv4, tail...); break;
        case IPProtNum::UDP : pop(stack, UDPHeader::create_from(ipv4), ipv4, tail...); break;
        case IPProtNum::ICMP: pop(stack, ICMPv4Header::create_from(ipv4), ipv4, tail...); break;
    }
}

// => IPv6 pop
template<typename ...Tail>
void pop(Stack& stack, IPv6Header& ipv6, Tail& ...tail) {
    switch (ipv6.getNextHeader()) {
        case IPv6NextHeader::TCP : pop(stack, TCPHeader::create_from(ipv6), ipv6, tail...); break;
        case IPv6NextHeader::UDP : pop(stack, UDPHeader::create_from(ipv6), ipv6, tail...); break;
        case IPv6NextHeader::ICMP: pop(stack, ICMPv6Header::create_from(ipv6), ipv6,  tail...); break;
    }
}

// => VLAN pop
template<typename ...Tail>
void pop(Stack& stack, VLANHeader& vlan, Tail& ...tail) {
    switch (vlan.getEtherType()) {
        case EtherType::ARP : pop(stack, ARPHeader::create_from(vlan), vlan, tail...); break;
        case EtherType::IPv4: pop(stack, IPv4Header::create_from(vlan), vlan, tail...); break;
        case EtherType::IPv6: pop(stack, IPv6Header::create_from(vlan), vlan, tail...); break;
        case EtherType::VLAN: break; // only one vlan tag allowed
    }
}


// => Ethernet pop
void pop(Stack& stack, EthernetHeader& eth) {
    switch (eth.getEtherType()) {
        case EtherType::ARP : pop(stack, ARPHeader::create_from(eth), eth); break;
        case EtherType::IPv4: pop(stack, IPv4Header::create_from(eth), eth); break;
        case EtherType::IPv6: pop(stack, IPv6Header::create_from(eth), eth); break;
        case EtherType::VLAN: pop(stack, VLANHeader::create_from(eth), eth); break;
    }
}

// ^ Pop from L2 up to top-level protocol should be *very* fast.


int main()
{   
    Stack stack;
    
    // register the routes
    // note: the plus sign converts the lambda to a function pointer. E.g. `+[]{}` becomes void(*)()
    // note: we could also use function pointers instead of lambda
    
    // register icmpv4 route
    stack.register_route(+[](ICMPv4Header& icmp, IPv4Header& ipv4, EthernetHeader& eth) {/**
        // EXAMPLE IMPLEMENTATION
        // ICMP reply immediately
        Packet packet;
        packet.push_front(flip_header(icmp)); // flip source and destination fields
        packet.push_front(flip_header(ipv4));
        packet.push_front(flip_header(eth));
        stack.push(packet);
    */});
    
    // register arp route
    stack.register_route(+[](ARPHeader& arp, EthernetHeader& eth) {/**
        // EXAMPLE IMPLEMENTATION
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
    
    // register tcp route
    stack.register_route(+[](TCPHeader& tcp, IPv4Header& ipv4, EthernetHeader& eth) {/**
        // Establish connection or pop to existing connection.
    */});
    
    
    // - DHCP can also be registered as a route because it uses fixed port numbers (67 for server and 68 for client).
    // - HTTP has no fixed port numbers so it will be need to be popd dynamically.
    // - Even though there are many combinations only a few need to be registered:
    //      -> There are 15 possible routes (with PPPoE this will become 30).
    //      -> Setting up a stack for TCP only requires registration of three routes:
    //          1. ethernet->arp
    //          2. ethernet->ipv4->udp->dhcp
    //          3. ethernet->ipv4->tcp
    // - Pop is very fast
    // - No creation of unneeded sessions (and no cleanup required)
    // - When a session is created all lower layer protocols are known at compile time. This allows us to
    //   implement a generic push function without any branches/indirections. Possibly we could even have
    //   single composite header object for all protocols.
    
    // Outgoing sessions should be similar. (Dunno how yet.)

    
    // test if it compiles
    EthernetHeader fake_ethernet_header;
    pop(stack, fake_ethernet_header);
}




