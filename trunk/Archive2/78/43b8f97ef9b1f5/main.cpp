#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>
#include <utility>
#include <typeinfo>

#define TRACE() std::cout << __PRETTY_FUNCTION__ << std::endl;

struct Ethernet {};
struct IPv4 {};
struct TCP {};

enum class EtherType { IPv4 };
enum class IPProtNum { TCP };

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
    Stack(Stack<>&& llps) : Stack<>(std::move(llps)) {}
    virtual Stack<>* create(const std::type_info* info);
};

template<>
struct Stack<IPv4, Ethernet> : Stack<Ethernet> {
    Stack(Stack<Ethernet>&& ethernet_stack);
    virtual Stack<>* create(const std::type_info* info);
};

template<>
struct Stack<TCP, IPv4, Ethernet> : Stack<IPv4, Ethernet> {
    Stack(Stack<IPv4, Ethernet>&&);
    void pop(const std::string& data) override;
    uint16_t mLocalPort = 1234;
};

Stack<>* Stack<>::create(const std::type_info* info) {
    if (info == &typeid(Ethernet)) return new Stack<Ethernet>(std::move(*this));
    throw std::runtime_error("Error");
}

Stack<IPv4, Ethernet>::Stack(Stack<Ethernet>&& llps) : Stack<Ethernet>(std::move(llps)) {
}
    
    Stack<>* Stack<Ethernet>::create(const std::type_info* info) {
    if (info == &typeid(IPv4)) return new Stack<IPv4, Ethernet>(std::move(*this));
    throw std::runtime_error("Error");
}

Stack<TCP, IPv4, Ethernet>::Stack(Stack<IPv4, Ethernet>&& llps) : Stack<IPv4, Ethernet>(std::move(llps)) {
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
    if (!validate(tcpdec) || tcpdec.getDestinationPort() != mLocalPort) return;
    std::cout << "TCP validation OK\n";
    
    
    std::cout << "Processing incoming TCP segment...\n";
    
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

