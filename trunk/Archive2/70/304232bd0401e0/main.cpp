
template<typename ...T>
struct _ {};


struct Eth {};
struct VLAN {};
struct ARP {};
struct IPv4 {};
struct ICMPv4 {};
struct IPv6 {};
struct ICMPv6 {};
struct TCP {};
struct UDP {};
struct App {};


template<typename>
struct Traits
{
    using Routes = _<>;
};


template<typename Tag>
using GetRoutes = typename Traits<Tag>::Routes;

template<>
struct Traits<UDP>
{
    using HL = _<App>;
    
    using Routes = _<
        _<UDP, _<App>>
    >;
};
template<>
struct Traits<TCP>
{
    using HL = _<App>;
    
    using Routes = _<
        _<TCP, _<App>>
    >;
};


template<> 
struct Traits<IPv6>
{
    using HL = _<ICMPv6, TCP, UDP>;
    
    using Routes = _<
        _<IPv6, GetRoutes<ICMPv6>>,
        _<IPv6, GetRoutes<TCP>>,
        _<IPv6, GetRoutes<UDP>>
    >;
};

template<> 
struct Traits<IPv4>
{
    using HL = _<ICMPv4, TCP, UDP>;
    
    using Routes = _<
        _<IPv4, GetRoutes<ICMPv4>>,
        _<IPv4, GetRoutes<TCP>>,
        _<IPv4, GetRoutes<UDP>>
    >;
};

template<> 
struct Traits<VLAN>
{
    using HL = _<IPv4, IPv6>;
    
    using Routes = _<
        _<VLAN, GetRoutes<IPv4>>,
        _<VLAN, GetRoutes<IPv6>>
    >;
};


template<>
struct Traits<Eth>
{
    using HL = _<ARP, IPv4, IPv6>;
    
    // 
    using Routes = _<
        _<Eth, GetRoutes<ARP>>,
        _<Eth, GetRoutes<IPv4>>,
        _<Eth, GetRoutes<IPv6>>
    >;
};


struct Stack : _<
    _<Eth, ARP>,
    _<Eth, IPv4, ICMPv4>,
    _<Eth, IPv4, TCP>
>{};




#include <iostream>
#include <memory>
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



int main()
{
    GetRoutes<Eth> routes;
    std::cout << Demangle(typeid(routes).name()) << std::endl;
}