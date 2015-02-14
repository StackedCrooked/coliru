#include <cstdlib>
#include <iostream>
#include <new>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <cxxabi.h>

#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;


std::string Demangle(char const * name)
{
    int st;
    char * const p = abi::__cxa_demangle(name, 0, 0, &st);
    switch (st)
    {
        case 0: { return std::unique_ptr<char, decltype(&std::free)>(p, &std::free).get(); }
        case -1: throw std::runtime_error("A memory allocation failure occurred.");
        case -2: throw std::runtime_error("Not a valid name under the GCC C++ ABI mangling rules.");
        case -3: throw std::runtime_error("One of the arguments is invalid.");
        default: throw std::runtime_error("unexpected demangle status");
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

enum PID { IPv4, IPv6 };


template<PID> struct PID2Type_;
template<> struct PID2Type_<IPv4> { using type = IPv4Protocol; };
template<> struct PID2Type_<IPv6> { using type = IPv6Protocol; };


template<PID pid>
using PID2Type = typename PID2Type_<pid>::type;

enum class EtherType { IPv4, IPv6 };



struct AbstractStack
{
    virtual ~AbstractStack() {}

    virtual void upgrade(PID) = 0;
};


template<typename ...Protocols>
struct Stack;



template<PID pid, typename ...T>
void upgrade_to(Stack<T...>* stack)
{
    using HLP = PID2Type<pid>;
    using LLStack = Stack<T...>;
    using HLStack = Stack<HLP, T...>;
    std::cout << "Upgrading " << GetTypeName<LLStack>() << " to " << GetTypeName<HLStack>() << std::endl;
    HLStack hlstack(std::move(*stack));
    stack->~Stack<T...>();
    new (stack) HLStack(std::move(hlstack));
}


template<>
struct Stack<EthernetProtocol> : AbstractStack
{
    Stack() {}
    void upgrade(PID pid) override
    {
        switch (pid)
        {
            case IPv4: upgrade_to<IPv4>(this); return;
            case IPv6: upgrade_to<IPv6>(this); return;
        }
    }
};




#define STACK(Name, ...) \
    template<> struct Stack<Name, __VA_ARGS__> : Stack<__VA_ARGS__> { \
		using Self = Stack<Name, __VA_ARGS__>;  \
		using LLStack = Stack<__VA_ARGS__>;  \
        explicit Stack(LLStack&& llstack)  : LLStack(std::move(llstack)) {} \
		template<typename T> using UpgradeTo = Stack<Name, T>; \
		void upgrade(PID) override; \
        Name m##Name; \
	};

#define UPGRADE(...) \
	template<> void Stack<__VA_ARGS__>::upgrade



//STACK(EthernetProtocol, IPv4Protocol, IPv6Protocol)
template<>
struct Stack<IPv4Protocol, EthernetProtocol> : Stack<EthernetProtocol>
{
    explicit Stack(Stack<EthernetProtocol>&& llp) : Stack<EthernetProtocol>(std::move(llp)) {  }

    void upgrade(PID pid) override
    {
        switch (pid)
        {
            case IPv4: std::cout << "I AM ALREADY IPv4" << std::endl; return;
            case IPv6: upgrade_to<IPv6>(this); return;
        }
    }
    IPv4Protocol mIPv4Protocol;
};

template<>
struct Stack<IPv6Protocol, EthernetProtocol> : Stack<EthernetProtocol>
{
    explicit Stack(Stack<EthernetProtocol>&& llp) : Stack<EthernetProtocol>(std::move(llp)) {  }

    void upgrade(PID pid) override
    {
    }
    IPv6Protocol mIPv6Protocol;
};


template<>
struct Stack<IPv6Protocol, IPv4Protocol, EthernetProtocol> : Stack<IPv4Protocol, EthernetProtocol>
{
    explicit Stack(Stack<IPv4Protocol, EthernetProtocol>&& llp) : Stack<IPv4Protocol, EthernetProtocol>(std::move(llp)) {  }

    void upgrade(PID pid) override
    {
        //if (pid == TCP) upgrade_to<TCP>(this); return;
    }

    IPv6Protocol mIPv6Protocol;
};



int main()
{
    long storage[100];
    AbstractStack* stack = new (storage) Stack<EthernetProtocol>();
    
    stack->upgrade(IPv4);
    stack->upgrade(IPv6);
}
