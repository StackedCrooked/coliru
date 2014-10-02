
// A protocol stack is simple to represent as diagram:
// +----------
// |   TCP   |   (has local port)
// +----------
// |   IP4   |   (has local ip)
// +----------
// |   ETH   |   (has local mac)
// +----------
//
// Or with VLAN:
// +----------
// |   L5    |   user program
// +----------
// |   TCP   |   local port
// +----------
// |   IP4   |   local ip
// +----------
// |   VLAN  |   vlan tag
// +----------
// |   ETH   |   local mac
// +----------
//
//
// It's also simple to represent as a class template:
// Stack<TCP, IPv4, Ethernet> or Stack<TCP, IPv4, VLAN, Ethernet>
//
// However, the configuration of the stack is determined at run-time
// using API calls like "Layer2.Set", "Layer3.Set", "Protocol.Add" etc....
//
// This example shows a way to bridge the runtime with the compile-time.


#include <iostream>
#include <array>
#include <memory>
#include <string>
#include <stdexcept>
#include <utility>
#include <typeinfo>


//
// HELPER STUFF
//
#define TRACE() std::cout << "TRACE: " << __FILE__ << ":" << __LINE__ << ": " << __PRETTY_FUNCTION__ << std::endl;

struct Ethernet {};
struct IPv4 {};
struct TCP {};

enum class EtherType : uint16_t { IPv4 };
enum class IPProtNum : uint8_t { TCP };

typedef std::array<uint8_t, 6> MACAddress;
typedef std::array<uint8_t, 4> IPv4Address;
struct EthernetHeader { MACAddress mDestinationMAC; MACAddress mSourceMAC; EtherType mEtherType; } ;
struct IPv4Header { IPv4Address mSourceIP; IPv4Address mDestinationIP; };
struct TCPHeader { uint16_t mDestinationPort; uint16_t mSourcePort;};

struct EthernetDecoder {
    EthernetDecoder(const std::string&) {}
    EtherType getEtherType() const { return EtherType::IPv4; }
    friend bool validate(EthernetDecoder) { return true; }
};

struct IPv4Decoder {
    IPv4Decoder(EthernetDecoder) {}
    IPProtNum getIPProtNum() const { return IPProtNum::TCP; }
    friend bool validate(IPv4Decoder) { return true; }
};

struct TCPDecoder {
    TCPDecoder(IPv4Decoder) {}
    uint16_t getDestinationPort() const { return 1234; }
    friend bool validate(TCPDecoder) { return true; }
};


//
// STACK CLASS
//
template<typename ...>
struct Stack;


template<>
struct Stack<>
{
    virtual ~Stack() = default;

    // Pops a packet.
    virtual void pop(const std::string&) {}

    // Returns an upgraded version of the current stack.
    virtual Stack<>* upgrade(const std::type_info* higher_layer);
};


template<>
struct Stack<Ethernet> : Stack<>
{
    Stack(Stack<>&& lower_layer_stack);
    Stack<>* upgrade(const std::type_info* higher_layer) override;
};


template<>
struct Stack<IPv4, Ethernet> : Stack<Ethernet> // note the inheritance pattern
{
    Stack(Stack<Ethernet>&& ethernet_stack);
    Stack<>* upgrade(const std::type_info* higher_layer) override;
};


template<>
struct Stack<TCP, IPv4, Ethernet> : Stack<IPv4, Ethernet>
{
    Stack(Stack<IPv4, Ethernet>&&);
    void pop(const std::string& data) override final;
};


// IMPLEMENTATIONS
Stack<>* Stack<>::upgrade(const std::type_info* higher_layer)
{
    if (higher_layer == &typeid(Ethernet))
    {
        return new Stack<Ethernet>(std::move(*this));
    }
//    else if (higher_layer == &typeid(VLAN))
//    {
//        return new Stack<VLAN, Ethernet>(std::move(this));
//    }
    else
    {
        throw std::runtime_error("Invalid higher layer protocol: " + std::string() + higher_layer->name());
    }
}


// ETHERNET STACK
Stack<Ethernet>::Stack(Stack<>&& lower_layer_stack) : Stack<>(std::move(lower_layer_stack)) // using move construction
{
    std::cout << "Upgrading to Ethernet stack.\n";
}

Stack<>* Stack<Ethernet>::upgrade(const std::type_info* higher_layer)
{
    if (higher_layer == &typeid(IPv4))
    {
        return new Stack<IPv4, Ethernet>(std::move(*this));
    }
    else
    {
        throw std::runtime_error("Invalid higher layer protocol: " + std::string() + higher_layer->name());
    }
}


// IPv4/ETHERNET STACK
Stack<IPv4, Ethernet>::Stack(Stack<Ethernet>&& lower_layer_stack) : Stack<Ethernet>(std::move(lower_layer_stack))
{
    std::cout << "Upgrading to IPv4/Ethernet stack.\n";
}


Stack<>* Stack<IPv4, Ethernet>::upgrade(const std::type_info* higher_layer)
{
    if (higher_layer == &typeid(TCP))
    {
        return new Stack<TCP, IPv4, Ethernet>(std::move(*this));
    }
    else
    {
        throw std::runtime_error("Invalid higher layer protocol: " + std::string() + higher_layer->name());
    }
}


// TCP/IPv4/ETHERNET STACK
Stack<TCP, IPv4, Ethernet>::Stack(Stack<IPv4, Ethernet>&& lower_layer_stack) : Stack<IPv4, Ethernet>(std::move(lower_layer_stack))
{
    std::cout << "Upgrading to TCP/IPv4/Ethernet stack.\n";
}


void Stack<TCP, IPv4, Ethernet>::pop(const std::string& data)
{

    // NOTE:
    // Code below is a hard-coded implementation for the TCP/IPv4/Ethernet combo.
    // This is makes it easy to understand. A real implementation would be generic.

    EthernetDecoder ethdec(data);
    if (!validate(ethdec) || ethdec.getEtherType() != EtherType::IPv4)
    {
        return;
    }

    IPv4Decoder ipdec(ethdec);
    if (!validate(ipdec) || ipdec.getIPProtNum() != IPProtNum::TCP)
    {
        return;
    }

    TCPDecoder tcpdec(ipdec);
    if (!validate(tcpdec) || tcpdec.getDestinationPort() != 1234)
    {
        return;
    }
    

    #if 0
    // one session to rule them all
    Session<TCP, IPv4, Ethernet> session;
    #endif
    
    std::cout << "popped\n";
}



int main()
{
    // User script and how it translates to C++ server code:

    // $server Port.Create "trunk-1-1"
    std::unique_ptr<Stack<>> stack(new Stack<>());

    // $port Layer2.Set "ethii"
    stack.reset(stack->upgrade(&typeid(Ethernet)));

    // $port Layer3.Set "ipv4"
    stack.reset(stack->upgrade(&typeid(IPv4)));

    // $port Protocol.Http.Client.Add
    stack.reset(stack->upgrade(&typeid(TCP)));

    // NOTE: HTTPProtocol would be replaced by HTTPClientController

    // quick test: pop is 1 virtual method call
    stack->pop("hello");
}


// NOTES:

// Disadvantages:
// - Untested in real life. There could be unforeseen problems with this design.
// - It's a big refactoring. Will need to test everything again.
// - Less dynamic, maybe.
// - This does not simplify complex protocols like TCP and IPv6.


// Advantages:
// - Probably much faster than current design.
// - Simplified session management.
// - More opportunity for parallelization due to less data sharing between sessions.


// Note:
// For improved enacapsulation we may opt to split off the link-layer part of the session.
