#include <string>

// Adding methods to a class without touching the original header file.
// (almost)


// Port.h:
    struct Port
    {
        template<typename T>
        T& addProtocol(); // undefined here
    };


// IPv4.h:
    struct IPv4
    {
        static IPv4& Create(Port& port) { return *(IPv4*)nullptr; }
        
        void configure(std::string ip, std::string netmask, std::string gateway)
        {
            // etc...
        }
    };


// IPv4.cpp:
    template<>
    IPv4& Port::addProtocol<IPv4>()
    {
        return IPv4::Create(*this);
    }


// IPv6.h:
    struct IPv6
    {
        static IPv6& Create(Port& port);
    };
    

// IPv6.cpp:
    template<>
    IPv6& Port::addProtocol<IPv6>()
    {
        // Use the nullptr allocator. 
        return *(IPv6*)nullptr;
    }



// User code
//#include "IPv4.h"

void work(Port& port)
{
    auto& ipv4 = port.addProtocol<IPv4>();
    ipv4.configure("10.8.0.23", "255.255.255.0", "10.8.0.2");
    // ...
}


int main()
{
    Port p;
    work(p);
}