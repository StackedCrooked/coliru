#include <cassert>
#include <cstdlib>
#include <iostream>
#include <new>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <cxxabi.h>

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
struct IPv4Protocol {};
struct IPv6Protocol {};
struct TCPProtocol {};

enum PID { IPv4, IPv6, TCP };

std::ostream& operator<<(std::ostream& os, PID pid)
{
    switch (pid)
    {
        case IPv4: return os << "IPv4";
        case IPv6: return os << "IPv6";
        case TCP: return os << "TCP";
    }
    return os;
}


template<PID> struct PID2Type_;
template<typename P> struct Type2PID_;

#define PID_TO_TYPE(p) \
    template<> struct PID2Type_<p> { using type = p##Protocol; }; \
    template<> struct Type2PID_<p##Protocol> { static constexpr PID value = p; };

PID_TO_TYPE(IPv4)
PID_TO_TYPE(IPv6)
PID_TO_TYPE(TCP)

template<PID pid>
using PID2Type = typename PID2Type_<pid>::type;

enum class EtherType { IPv4, IPv6 };



struct AbstractStack
{
    virtual ~AbstractStack() {}

    void upgrade(PID pid)
    {
        do_upgrade(pid, nullptr);
    }

    template<typename HLP>
    void upgrade(HLP& hlp)
    {
        do_upgrade(Type2PID_<HLP>::value, &hlp);
    }

    virtual void do_upgrade(PID, void*) = 0;
};


template<typename ...Protocols>
struct Stack;


template<typename ...LLP> struct Upgrade
{
    void operator()(Stack<LLP...>&, PID pid)
    {
    }
};

//template<typename ...LLP>

template<PID pid, typename ...T>
void upgrade_to(Stack<T...>& stack)
{
    TRACE
    using HLP = PID2Type<pid>;
    using HLStack = Stack<HLP, T...>;
    std::cout << "Upgrading to " << GetTypeName<HLStack>() << std::endl;
    HLStack hlstack(std::move(stack));
    stack.~Stack<T...>();
    new(&stack) HLStack(std::move(hlstack));
}


template<>
struct Stack<EthernetProtocol> : AbstractStack, EthernetProtocol
{
    Stack() {}
    void do_upgrade(PID pid, void* hlp) override
    {
        TRACE
        switch (pid)
        {
            case IPv4:
                upgrade_to<IPv4>(*this); // TODO: USE HLP
                return;
            case IPv6:
                upgrade_to<IPv6>(*this);
                return;
            case TCP:
                std::cout << "TCP does not rest directly on top of Ethernet dumbass!" << std::endl;
        }
    }
};


template<typename CLP, typename ...LLP>
struct Stack<CLP, LLP...> : Stack<LLP...>
{
    explicit Stack(Stack<LLP...>&& llp) : Stack<LLP...>(std::move(llp)) {  }

    void do_upgrade(PID pid, void* hlp) override
    {
        TRACE
        Upgrade<CLP, LLP...>()(*this, pid);
    }
};


template<typename ...LLP>
struct Upgrade<IPv4Protocol, LLP...>
{
    void operator()(Stack<IPv4Protocol, LLP...>& stack, PID pid)
    {
        assert(pid != IPv4);
        if (pid == IPv6) upgrade_to<IPv6>(stack); return;
        if (pid == TCP) upgrade_to<TCP>(stack); return;
    }
};


template<typename ...LLP>
struct Upgrade<IPv6Protocol, LLP...>
{
    void operator()(Stack<IPv6Protocol, LLP...>& stack, PID pid)
    {
        assert(pid != IPv6);
        if (pid == TCP) upgrade_to<TCP>(stack); return;
    }
};

template<typename ...LLP>
struct Upgrade<IPv6Protocol, IPv4Protocol, LLP...>
{
    void operator()(Stack<IPv6Protocol, IPv4Protocol, LLP...>& stack, PID pid)
    {
        assert(pid != IPv4);
        assert(pid != IPv6);
        if (pid == TCP) upgrade_to<TCP>(stack); return;
    }
};

template struct Stack<IPv4Protocol, EthernetProtocol>;
template struct Stack<TCPProtocol, IPv4Protocol, EthernetProtocol>;
template struct Stack<IPv6Protocol, IPv4Protocol, EthernetProtocol>;
template struct Stack<TCPProtocol, IPv6Protocol, EthernetProtocol>;
template struct Stack<TCPProtocol, IPv6Protocol, IPv4Protocol, EthernetProtocol>;


int main()
{
    long storage[100];
    std::cout << std::endl; { AbstractStack* stack = new(storage) Stack<EthernetProtocol>(); stack->upgrade(IPv4); stack->upgrade(TCP); }
    std::cout << std::endl; { AbstractStack* stack = new(storage) Stack<EthernetProtocol>(); stack->upgrade(IPv6); stack->upgrade(TCP); }
    std::cout << std::endl; { AbstractStack* stack = new(storage) Stack<EthernetProtocol>(); stack->upgrade(IPv4); stack->upgrade(IPv6); stack->upgrade(TCP); }


    AbstractStack& stack = *new (storage) Stack<EthernetProtocol>();

    IPv4Protocol ip;
    TCPProtocol tcp;
    stack.upgrade(ip);
    stack.upgrade(tcp);
}
