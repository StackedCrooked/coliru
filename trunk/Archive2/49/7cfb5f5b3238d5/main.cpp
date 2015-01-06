#include <iostream>
#include <memory>
#include <typeindex>
#include <string>
#include <vector>
#include <stdexcept>
#include <cxxabi.h>


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



#define TRACE std::cout << __FILE__ << ":" << __LINE__ << " \t" << __PRETTY_FUNCTION__ << std::endl;

template<typename ...Args>
void eval(Args&& ...) {}



template<typename ...HLP>
struct Protocol;


struct ProtocolInterface
{
    virtual ~ProtocolInterface  () {}
};


struct AbstractProtocol : virtual ProtocolInterface
{
    AbstractProtocol()
    {
    }

    virtual ~AbstractProtocol  () {}

    virtual bool receive(const std::string&) = 0;

    virtual AbstractProtocol* extend(std::type_index tid) = 0;

    template<typename Derived>
    Derived& downcast()
    {
        std::cout << "Downcasting " << Demangle(typeid(*this).name()) << " to " << Demangle(typeid(Derived).name()) << std::endl;
        return dynamic_cast<Derived&>(*this);
    }
};



template<typename ...>
struct GetHead;


template<typename Head>
struct GetHead<Head>
{
    using type = Head;
};


template<typename Head, typename ...Tail>
struct GetHead<Head, Tail...>
{
    using type = Head;
};

template<typename ...HLP>
struct Protocol;


template<typename CLP>
struct Protocol<CLP> : virtual AbstractProtocol, CLP
{
    Protocol(CLP clp = CLP{}) :
        AbstractProtocol(*this),
        CLP(clp)
    {
    }

    Protocol<CLP>& getCLP()
    {
        return *this;
    }

    bool check_relevance(const std::string& s)
    {
        TRACE
        CLP& clp = *this;
        return clp.check_relevance(s);
    }

    bool receive(const std::string& s) override
    {
        TRACE
        return check_relevance(s);
    }

    AbstractProtocol* extend(std::type_index tid) override
    {
        return Extend(tid, *this);
    }
};


template<typename CLP, typename LLP>
struct Protocol<CLP, LLP> :
    virtual AbstractProtocol,
    Protocol<CLP>,
    Protocol<LLP>
{
    static Protocol* Create(LLP llp)
    {
        return new Protocol<CLP, LLP>(llp);
    }

    Protocol(CLP clp, LLP llp) :
        AbstractProtocol(),
        Protocol<CLP>(clp),
        Protocol<LLP>(llp)
    {
    }

    Protocol(LLP llp) :
        AbstractProtocol(),
        Protocol<CLP>(),
        Protocol<LLP>(llp)
    {
    }

    Protocol<CLP>& getCLP() { return *this; }

    Protocol<LLP>& getLLP() { return *this; }

    bool check_relevance(std::string s)
    {
        TRACE
        return getLLP().check_relevance(s) && getCLP().check_relevance(s);
    }

    bool receive(const std::string& s) override
    {
        TRACE
        return check_relevance(s);
    }


    AbstractProtocol* extend(std::type_index tid) override
    {
        return Extend(tid, *this);
    }

};


template<typename CLP, typename Head, typename ...Tail>
struct Protocol<CLP, Head, Tail...> :
    virtual AbstractProtocol,
    Protocol<CLP>,
    Protocol<Head, Tail...>
{
    static Protocol* Create(Protocol<Head, Tail...> llp)
    {
        return new Protocol<CLP, Head, Tail...>(llp);
    }

    Protocol(Protocol<Head, Tail...> llp) :
        AbstractProtocol(),
        Protocol<CLP>(),
        Protocol<Head, Tail...>(llp)
    {
    }

    Protocol<CLP>& getCLP() { return *this ; }


    bool check_relevance(const std::string& s)
    {
        TRACE
        return getLLP().check_relevance(s) && getCLP().check_relevance(s);
    }


    Protocol<Head, Tail...>& getLLP()
    {
        return *this;
    }

    bool receive(const std::string& s) override
    {
        TRACE
        return check_relevance(s);
    }

    AbstractProtocol* extend(std::type_index tid) override
    {
        return Extend(tid, *this);
    }
};



template<typename Derived>
struct CRTP : virtual ProtocolInterface
{
    bool check_relevance(const std::string& s)
    {
        std::cout << Demangle(typeid(Derived).name()) << "::check_relevance(\"" << s << "\")" << std::endl;
        return static_cast<Derived&>(*this).do_check_relevance(s);
    }
};





struct Stack
{
    Stack();

    template<typename CLP>
    bool acquire()
    {
        mProtocol.reset(mProtocol->extend(typeid(CLP)));
        return true;
    }

    void receive(const std::string& s)
    {
        AbstractProtocol& p = *mProtocol;
        p.receive(s);
    }

    std::unique_ptr<AbstractProtocol> mProtocol;
};


struct Ethernet : CRTP<Ethernet>
{
    Ethernet(const std::string& inMAC = "") : mMAC(inMAC) {}

    bool do_check_relevance(const std::string& s)
    {
        return s.find("Ethernet") != std::string::npos;
    }

    AbstractProtocol* extend(std::type_index tid);

    std::string mMAC;
};


struct ARP : CRTP<ARP>
{
    bool do_check_relevance(const std::string& s)
    {
        return s.find("ARP") != std::string::npos;
    }
};


struct VLAN : CRTP<VLAN>
{
    bool do_check_relevance(const std::string& s)
    {
        return s.find("VLAN") != std::string::npos;
    }
};


struct IPv4 : CRTP<IPv4>
{
    IPv4(const std::string& inIP = "") : mIP(inIP) {}

    bool do_check_relevance(const std::string& s)
    {
        return s.find("IPv4") != std::string::npos;
    }

    std::string mIP;
};


struct IPv6 : CRTP<IPv6>
{
    IPv6() {}

    bool do_check_relevance(const std::string& s)
    {
        return s.find("IPv6") != std::string::npos;
    }
};


struct TCP : CRTP<TCP>
{
    TCP() {}

    bool do_check_relevance(const std::string& s)
    {
        return s.find("TCP") != std::string::npos;
    }
};


struct HTTP : CRTP<HTTP>
{
    HTTP() {}

    bool do_check_relevance(const std::string& s)
    {
        return s.find("HTTP") != std::string::npos;
    }
};



template<typename ...LLP>
AbstractProtocol* Extend(std::type_index tid, Protocol<LLP...>& llp)
{
    throw std::runtime_error(Demangle(tid.name()) + " " + Demangle(typeid(llp).name()) + " " + __PRETTY_FUNCTION__);
}


template<typename ...LLP>
AbstractProtocol* Extend(std::type_index tid, Protocol<Ethernet, LLP...>& eth)
{
    if (tid == typeid(ARP)) return Protocol<ARP, Ethernet, LLP...>::Create(eth);
    if (tid == typeid(VLAN)) return Protocol<VLAN, Ethernet, LLP...>::Create(eth);
    if (tid == typeid(IPv4)) return Protocol<IPv4, Ethernet, LLP...>::Create(eth);
    if (tid == typeid(IPv6)) return Protocol<IPv6, Ethernet, LLP...>::Create(eth);
    throw std::runtime_error(Demangle(tid.name()) + " > " + __PRETTY_FUNCTION__);
}


template<typename ...LLP>
AbstractProtocol* Extend(std::type_index tid, Protocol<VLAN, LLP...>& vlan)
{
    if (tid == typeid(ARP)) return Protocol<ARP, VLAN, LLP...>::Create(vlan);
    if (tid == typeid(IPv4)) return Protocol<IPv4, VLAN, LLP...>::Create(vlan);
    if (tid == typeid(IPv6)) return Protocol<IPv6, VLAN, LLP...>::Create(vlan);
    throw std::runtime_error(Demangle(tid.name()) + " > " + __PRETTY_FUNCTION__);
}


template<typename ...LLP>
AbstractProtocol* Extend(std::type_index tid, Protocol<IPv4, LLP...>& llp)
{
    if (tid == typeid(TCP)) return Protocol<TCP, IPv4, LLP...>::Create(llp);
    if (tid == typeid(IPv6)) return Protocol<IPv6, IPv4, LLP...>::Create(llp);
    throw std::runtime_error(Demangle(tid.name()) + " > " + __PRETTY_FUNCTION__);
}


template<typename ...LLP>
AbstractProtocol* Extend(std::type_index tid, Protocol<IPv6, LLP...>& llp)
{
    if (tid == typeid(TCP)) return Protocol<TCP, IPv6, LLP...>::Create(llp);
    throw std::runtime_error(Demangle(tid.name()) + " > " + __PRETTY_FUNCTION__);
}


template<typename ...LLP>
AbstractProtocol* Extend(std::type_index tid, Protocol<TCP, LLP...>& llp)
{
    if (tid == typeid(HTTP)) return Protocol<HTTP, TCP, LLP...>::Create(llp);
    throw std::runtime_error(Demangle(tid.name()) + " > " + __PRETTY_FUNCTION__);
}



Stack::Stack() : mProtocol(new Protocol<Ethernet>())
{
}



AbstractProtocol* Ethernet::extend(std::type_index tid)
{
    if (tid == typeid(ARP))
    {
        return Protocol<ARP, Ethernet>::Create(*this);
    }

    if (tid == typeid(VLAN))
    {
        return Protocol<VLAN, Ethernet>::Create(*this);
    }

    if (tid == typeid(IPv4))
    {
        return Protocol<IPv4, Ethernet>::Create(*this);
    }

    if (tid == typeid(IPv6))
    {
        return Protocol<IPv6, Ethernet>::Create(*this);
    }

    throw std::runtime_error(Demangle(tid.name()) + " > " + __PRETTY_FUNCTION__);
}



int main()
{
    Stack stack;
    stack.acquire<VLAN>();
    stack.acquire<IPv4>();
    stack.acquire<TCP>();
    stack.acquire<HTTP>();
    stack.receive("Ethernet VLAN IPv4 TCP HTTP");
}
