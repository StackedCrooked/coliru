#include <string>
#include <vector>


namespace RPC
{
    template<typename Signature>
    struct Command
    {
    };
}


namespace Communication
{       
    using RPC::Command;
    
    namespace Common
    {
        using IP = std::string;
        using MAC = std::string;
    }
    namespace Server
    {
        using InterfaceDescriptor = std::tuple<std::string>;
        using InterfaceDescriptors = std::vector<InterfaceDescriptor>;
        using GetInterfaceDescriptors = Command<InterfaceDescriptors()>;
        using PortId = std::string;
        using CreatePort = Command<PortId(void)>;
    }    
    namespace Ethernet
    {   
        using Common::MAC;
        using SetMAC = Command<void(MAC)>;
        using SetEncoding = Command<void(std::string)>;
    }    
    namespace IPv4
    {
        using Common::IP;
        using SetIP = Command<void(IP)>;
        using SetGW = Command<void(IP)>;
        using SetNM = Command<void(IP)>;
    }    
    namespace ICMP
    {
        using Common::IP;
        using SetDestination = Command<void(IP)>;
        using SetDataSize = Command<void(int)>;
    }
}


namespace Impl
{
    namespace EthernetImpl
    {
        using namespace Communication;
        using namespace Communication::Ethernet;
        
        struct SetMACImpl : SetMAC
        {
            void operator()(const MAC & ) const
            {
            }
        };
    }
    namespace IPv4Impl
    {
        using namespace Communication;
        using namespace Communication::IPv4;
        
        struct DoSetIP : SetIP
        {
            void operator()(const IP & ) const
            {
            }
        };
        
        struct DoSetGW : SetGW
        {
            void operator()(const IP & ) const
            {
            }
        };
        
        struct DoSetNM : SetNM
        {
            void operator()(const IP & ) const
            {
            }
        };
    }    
}
