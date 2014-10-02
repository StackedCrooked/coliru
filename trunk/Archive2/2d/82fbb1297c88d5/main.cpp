#include <iostream>
#include <array>
#include <memory>
#include <string>
#include <stdexcept>
#include <utility>
#include <typeinfo>

#define TRACE() std::cout << "TRACE: " << __FILE__ << ":" << __LINE__ << ": " << __PRETTY_FUNCTION__ << std::endl;

struct Ethernet {};
struct IPv4 {};
struct TCP {};

enum class EtherType : uint16_t { IPv4 };
enum class IPProtNum : uint8_t { TCP };

typedef std::array<uint8_t, 6> MACAddress;
typedef std::array<uint8_t, 4> IPv4Address;
struct alignas(alignof(uint16_t)) EthernetHeader { MACAddress mDestinationMAC; MACAddress mSourceMAC; EtherType mEtherType; } ;
struct alignas(alignof(uint16_t)) IPv4Header { IPv4Address mSourceIP; IPv4Address mDestinationIP; };
struct alignas(alignof(uint32_t)) TCPHeader { uint16_t mDestinationPort; uint16_t mSourcePort;};

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

struct ARP { void init() { std::cout << "Importing ARP functionality.\n"; } };
struct ICMPv4 { void init() { std::cout << "Importing ICMPv4 functionality.\n"; } };


template<typename ...>
struct Stack;

template<>
struct Stack<> {
    virtual ~Stack() {}    
    virtual void pop(const std::string& ) {}
    virtual Stack<>* create(const std::type_info* info);
};


template<>
struct Stack<Ethernet> : Stack<> {
    Stack(Stack<>&& llps) : Stack<>(std::move(llps)) {
        std::cout << "Creating Ethernet stack.\n";
    }
    virtual Stack<>* create(const std::type_info* info);
};

template<>
struct Stack<IPv4, Ethernet> : Stack<Ethernet>, ARP, ICMPv4 {
    Stack(Stack<Ethernet>&& ethernet_stack);
    virtual Stack<>* create(const std::type_info* info);
};

template<>
struct Stack<TCP, IPv4, Ethernet> : Stack<IPv4, Ethernet> {
    Stack(Stack<IPv4, Ethernet>&&);
    void pop(const std::string& data) override;
    
    struct CompositeHeader {
        EthernetHeader mEthernetHeader;
        IPv4Header mIPv4Header;
        TCPHeader mTCPHeader;
    }; 
    CompositeHeader mCompositeHeader;
};

Stack<>* Stack<>::create(const std::type_info* info) {
    if (info == &typeid(Ethernet)) return new Stack<Ethernet>(std::move(*this));
    throw std::runtime_error("Error");
}

Stack<IPv4, Ethernet>::Stack(Stack<Ethernet>&& llps) : Stack<Ethernet>(std::move(llps)) {
    std::cout << "Creating IPv4/Ethernet stack.\n";
}
    
Stack<>* Stack<Ethernet>::create(const std::type_info* info) {
    if (info == &typeid(IPv4)) return new Stack<IPv4, Ethernet>(std::move(*this));
    throw std::runtime_error("Error");
}

Stack<TCP, IPv4, Ethernet>::Stack(Stack<IPv4, Ethernet>&& llps) : Stack<IPv4, Ethernet>(std::move(llps)) {
    std::cout << "Creating TCP/IPv4/Ethernet stack.\n  ";
    ARP::init();
    std::cout << "  ";
    ICMPv4::init();
    mCompositeHeader.mTCPHeader.mDestinationPort = 1234;
}

Stack<>* Stack<IPv4, Ethernet>::create(const std::type_info* info) {
    if (info == &typeid(TCP)) return new Stack<TCP, IPv4, Ethernet>(std::move(*this));
    throw std::runtime_error("Invalid.");
}

void Stack<TCP, IPv4, Ethernet>::pop(const std::string& data) {
    TRACE();
    EthernetDecoder ethdec(data);
    if (!validate(ethdec) || ethdec.getEtherType() != EtherType::IPv4) return;
    std::cout << "Ethernet validation OK\n";
    
    IPv4Decoder ipdec(ethdec);
    if (!validate(ipdec) || ipdec.getIPProtNum() != IPProtNum::TCP) return;
    std::cout << "IPv4 validation OK\n";
    
    TCPDecoder tcpdec(ipdec);
    if (!validate(tcpdec) || tcpdec.getDestinationPort() != mCompositeHeader.mTCPHeader.mDestinationPort) return;
    std::cout << "TCP validation OK\n";
    
    // session header is same as incoming header but with source and destination fields swapped
    CompositeHeader session_header = mCompositeHeader;
    std::swap(session_header.mEthernetHeader.mSourceMAC , session_header.mEthernetHeader.mDestinationMAC);
    std::swap(session_header.mIPv4Header.mSourceIP      , session_header.mIPv4Header.mDestinationIP     );
    std::swap(session_header.mTCPHeader.mSourcePort     , session_header.mTCPHeader.mDestinationPort    );
    
    std::cout << "Creating TCP connection..\n";
    
    
    // ...
}


int main()
{
    std::unique_ptr<Stack<>> stack(new Stack<>());
    
    // $port Laye2.Set(ethii)
    stack.reset(stack->create(&typeid(Ethernet)));
    
    // $port Layer3.Set(ipv4)
    stack.reset(stack->create(&typeid(IPv4)));
    
    // $port Protocol.Http.Client.Add
    stack.reset(stack->create(&typeid(TCP)));
    
    stack->pop("hello");
    
    
}

