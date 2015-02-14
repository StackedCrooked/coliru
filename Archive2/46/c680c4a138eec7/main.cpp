#include <cassert>
#include <cstdlib>
#include <iostream>
#include <new>
#include <memory>
#include <stdexcept>
#include <sstream>
#include <string>
#include <utility>
#include <cxxabi.h>


enum ProtocolNumber
{
    VLAN,
    IPv4,
    IPv6,
    TCP
};


std::ostream& operator<<(std::ostream& os, ProtocolNumber pid);


std::string to_string(ProtocolNumber p)
{
    std::stringstream ss;
    ss << p;
    return ss.str();
}


#define TRACE //std::cout << __PRETTY_FUNCTION__ << std::endl;


std::string Demangle(char const* name)
{
    int st;
    char* const p = abi::__cxa_demangle(name, 0, 0, &st);
    switch (st)
    {
        case 0:
        {
            return std::unique_ptr<char, decltype(&std::free)>(p, &std::free).get();
        }
        case -1:
            throw std::runtime_error("A memory allocation failure occurred.");
        case -2:
            throw std::runtime_error("Not a valid name under the GCC C++ ABI mangling rules.");
        case -3:
            throw std::runtime_error("One of the arguments is invalid.");
        default:
            throw std::runtime_error("unexpected demangle status");
    }
}

template<typename T>
std::string GetTypeName()
{
    return Demangle(typeid(T).name());
}



struct EthernetProtocol {};
struct VLANProtocol {};
struct IPv4Protocol {};
struct IPv6Protocol {};
struct TCPProtocol {};



std::ostream& operator<<(std::ostream& os, ProtocolNumber pid)
{
    switch (pid)
    {
        case VLAN: return os << "VLAN";
        case IPv4: return os << "IPv4";
        case IPv6: return os << "IPv6";
        case TCP: return os << "TCP";
    }
    return os;
}


template<ProtocolNumber> struct PID2Type_;
template<typename P> struct Type2PID_;

#define PID_TO_TYPE(p) \
    template<> struct PID2Type_<p> { using type = p##Protocol; }; \
    template<> struct Type2PID_<p##Protocol> { static constexpr ProtocolNumber value = p; };

PID_TO_TYPE(VLAN)
PID_TO_TYPE(IPv4)
PID_TO_TYPE(IPv6)
PID_TO_TYPE(TCP)

template<ProtocolNumber pid>
using PID2Type = typename PID2Type_<pid>::type;

enum class EtherType { IPv4, IPv6 };



struct AbstractStack
{
    virtual ~AbstractStack() {}

    void upgrade(ProtocolNumber pid)
    {
        std::cout << Demangle(typeid(*this).name()) << ": upgrade to " << pid;
        do_upgrade(pid, nullptr);
        std::cout << ". Our type is now: " << Demangle(typeid(*this).name()) << std::endl;
    }

    template<typename HLP>
    void upgrade(HLP& hlp)
    {
        std::cout << Demangle(typeid(*this).name()) << ": upgrade to " << Demangle(typeid(HLP).name());
        do_upgrade(Type2PID_<HLP>::value, &hlp);
        std::cout << ". Our type is now: " << Demangle(typeid(*this).name()) << std::endl;
    }

    virtual void do_upgrade(ProtocolNumber, void*)
    {
        throw std::runtime_error("");
    }
};


template<typename ...Protocols>
struct Stack;

template<typename ...LLP>
struct Upgrade;

template<ProtocolNumber pid, typename ...T>
void upgrade_to(Stack<T...>& stack)
{
    TRACE
    using HLP = PID2Type<pid>;
    using HLStack = Stack<HLP, T...>;
    HLStack hlstack(stack);
    stack.~Stack<T...>();
    new(&stack) HLStack(std::move(hlstack));
}

template<>
struct Stack<> : AbstractStack
{
};

template<>
struct Stack<EthernetProtocol> : Stack<>
{
    Stack() = default;
    
    Stack(const Stack&) = default;
    Stack& operator=(const Stack&) = default;
    virtual void do_upgrade(ProtocolNumber, void*) override;
};


void Stack<EthernetProtocol>::do_upgrade(ProtocolNumber pid, void*)
{
    TRACE
    switch (pid)
    {
        case VLAN: upgrade_to<VLAN>(*this); return;
        case IPv4: upgrade_to<IPv4>(*this); return;
        case IPv6: upgrade_to<IPv6>(*this); return;
        case TCP: throw std::logic_error("TCP is not on top of Ethernet");
    }
}


template<typename CLP, typename ...LLP>
struct Stack<CLP, LLP...> : Stack<LLP...>
{
    Stack(Stack<LLP...>& rhs) : Stack<LLP...>(rhs) { }
    Stack(const Stack<CLP, LLP...>&) = default;
    Stack& operator=(const Stack<CLP, LLP...>&) = default;
    virtual void do_upgrade(ProtocolNumber, void*) override;
};


template<> void Stack<IPv4Protocol, EthernetProtocol>::do_upgrade(ProtocolNumber pid, void* hlp)
{
    TRACE
    switch (pid)
    {
        case IPv6: upgrade_to<IPv6>(*this); return;
        case TCP: upgrade_to<TCP>(*this); return;
        default: throw std::logic_error(Demangle(typeid(*this).name()) + ": Invalid higher layer protocol: " + to_string(pid));
    }
}


template<> void Stack<TCPProtocol, IPv4Protocol, EthernetProtocol>::do_upgrade(ProtocolNumber pid, void* hlp)
{
    TRACE
    throw std::logic_error(Demangle(typeid(*this).name()) + ": Invalid higher layer protocol: " + to_string(pid));
}


template<> void Stack<IPv6Protocol, EthernetProtocol>::do_upgrade(ProtocolNumber pid, void* hlp)
{
    TRACE
    switch (pid)
    {
        case TCP: upgrade_to<TCP>(*this); return;
        default: throw std::logic_error(Demangle(typeid(*this).name()) + ": Invalid higher layer protocol: " + to_string(pid));
    }
}


template<> void Stack<TCPProtocol, IPv6Protocol, EthernetProtocol>::do_upgrade(ProtocolNumber pid, void* hlp)
{
    TRACE
    switch (pid)
    {
        default: throw std::logic_error(Demangle(typeid(*this).name()) + ": Invalid higher layer protocol: " + to_string(pid));
    }
}


template<> void Stack<IPv6Protocol, IPv4Protocol, EthernetProtocol>::do_upgrade(ProtocolNumber pid, void* hlp)
{
    TRACE
    switch (pid)
    {
        case TCP: upgrade_to<TCP>(*this); return;
        default: throw std::logic_error(Demangle(typeid(*this).name()) + ": Invalid higher layer protocol: " + to_string(pid));
    }
}


template<> void Stack<TCPProtocol, IPv6Protocol, IPv4Protocol, EthernetProtocol>::do_upgrade(ProtocolNumber pid, void* hlp)
{
    TRACE
    throw std::logic_error(Demangle(typeid(*this).name()) + ": Invalid higher layer protocol: " + to_string(pid));
}


template<> void Stack<VLANProtocol, EthernetProtocol>::do_upgrade(ProtocolNumber pid, void* hlp)
{
    TRACE
    switch (pid)
    {
        case IPv4: upgrade_to<IPv4>(*this); return;
        case IPv6: upgrade_to<IPv6>(*this); return;
        default: throw std::logic_error(Demangle(typeid(*this).name()) + ": Invalid higher layer protocol: " + to_string(pid));
    }
}


template<> void Stack<IPv4Protocol, VLANProtocol, EthernetProtocol>::do_upgrade(ProtocolNumber pid, void* hlp)
{
    TRACE
    switch (pid)
    {
        case IPv6: upgrade_to<IPv6>(*this); return;
        case TCP: upgrade_to<TCP>(*this); return;
        default: throw std::logic_error(Demangle(typeid(*this).name()) + ": Invalid higher layer protocol: " + to_string(pid));
    }
}


template<> void Stack<TCPProtocol, IPv4Protocol, VLANProtocol, EthernetProtocol>::do_upgrade(ProtocolNumber pid, void* hlp)
{
    TRACE
    switch (pid)
    {
        default: throw std::logic_error(Demangle(typeid(*this).name()) + ": Invalid higher layer protocol: " + to_string(pid));
    }
}


template<> void Stack<IPv6Protocol, VLANProtocol, EthernetProtocol>::do_upgrade(ProtocolNumber pid, void* hlp)
{
    switch (pid)
    {
        case TCP: upgrade_to<TCP>(*this); return;
        default: throw std::logic_error(Demangle(typeid(*this).name()) + ": Invalid higher layer protocol: " + to_string(pid));
    }
}


template<> void Stack<TCPProtocol, IPv6Protocol, VLANProtocol, EthernetProtocol>::do_upgrade(ProtocolNumber pid, void* hlp)
{
    switch (pid)
    {
        default: throw std::logic_error(Demangle(typeid(*this).name()) + ": Invalid higher layer protocol: " + to_string(pid));
    }
}


template<> void Stack<IPv6Protocol, IPv4Protocol, VLANProtocol, EthernetProtocol>::do_upgrade(ProtocolNumber pid, void* hlp)
{
    switch (pid)
    {
        case TCP: upgrade_to<TCP>(*this); return;
        default: throw std::logic_error(Demangle(typeid(*this).name()) + ": Invalid higher layer protocol: " + to_string(pid));
    }
}


template<> void Stack<TCPProtocol, IPv6Protocol, IPv4Protocol, VLANProtocol, EthernetProtocol>::do_upgrade(ProtocolNumber pid, void* hlp)
{
    switch (pid)
    {
        default: throw std::logic_error(Demangle(typeid(*this).name()) + ": Invalid higher layer protocol: " + to_string(pid));
    }
}




template<typename ...LLP>
struct Upgrade<TCPProtocol, LLP...>
{
    void operator()(Stack<TCPProtocol, LLP...>&, ProtocolNumber)
    {
        throw std::runtime_error(Demangle(typeid(*this).name()) + ": TCP is top-level");
    }
};


template<>
struct Upgrade<VLANProtocol, EthernetProtocol>
{
    void operator()(Stack<VLANProtocol, EthernetProtocol>& stack, ProtocolNumber pid)
    {
        if (pid == IPv4) upgrade_to<IPv4>(stack); return;
        if (pid == IPv6) upgrade_to<IPv6>(stack); return;
        std::stringstream ss;
        ss << GetTypeName<decltype(*this)>() + ": cannot be upgraded to " << pid;
        std::string s = ss.str(); std::cout << s << std::endl; throw std::runtime_error(ss.str());
    }
};


template<typename ...LLP>
struct Upgrade<IPv4Protocol, LLP...>
{
    void operator()(Stack<IPv4Protocol, LLP...>& stack, ProtocolNumber pid)
    {
        if (pid == IPv6) upgrade_to<IPv6>(stack); return;
        if (pid == TCP) upgrade_to<TCP>(stack); return;
        std::stringstream ss;
        ss << GetTypeName<decltype(*this)>() + ": cannot be upgraded to " << pid;
        std::string s = ss.str(); std::cout << s << std::endl; throw std::runtime_error(ss.str());
    }
};


template<typename ...LLP>
struct Upgrade<IPv6Protocol, IPv4Protocol, LLP...>
{
    void operator()(Stack<IPv6Protocol, IPv4Protocol, LLP...>& stack, ProtocolNumber pid)
    {
        assert(pid != IPv4);
        assert(pid != IPv6);
        if (pid == TCP) upgrade_to<TCP>(stack); return;
        std::stringstream ss;
        ss << GetTypeName<decltype(*this)>() + ": cannot be upgraded to " << pid;
        std::string s = ss.str(); std::cout << s << std::endl; throw std::runtime_error(ss.str());
    }
};


template struct Stack<EthernetProtocol>;
template struct Stack<IPv4Protocol, EthernetProtocol>;
template struct Stack<TCPProtocol, IPv4Protocol, EthernetProtocol>;
template struct Stack<IPv6Protocol, IPv4Protocol, EthernetProtocol>;
template struct Stack<TCPProtocol, IPv6Protocol, EthernetProtocol>;
template struct Stack<TCPProtocol, IPv6Protocol, IPv4Protocol, EthernetProtocol>;

template struct Stack<VLANProtocol, EthernetProtocol>;
template struct Stack<IPv4Protocol, VLANProtocol, EthernetProtocol>;
template struct Stack<IPv6Protocol, VLANProtocol, EthernetProtocol>;
template struct Stack<TCPProtocol, IPv4Protocol, VLANProtocol, EthernetProtocol>;
template struct Stack<TCPProtocol, IPv6Protocol, VLANProtocol, EthernetProtocol>;

template struct Stack<IPv6Protocol, IPv4Protocol, VLANProtocol, EthernetProtocol>;
template struct Stack<TCPProtocol, IPv6Protocol, IPv4Protocol, VLANProtocol, EthernetProtocol>;


int main()
{
    VLANProtocol vlan;
    IPv4Protocol ip;
    IPv6Protocol ip6;
    TCPProtocol tcp;


    long storage[100];
    AbstractStack& stack = *new (storage) Stack<EthernetProtocol>();

    stack.upgrade(vlan);
    stack.upgrade(ip);
    stack.upgrade(ip6); // dual stack
    stack.upgrade(tcp);
}
