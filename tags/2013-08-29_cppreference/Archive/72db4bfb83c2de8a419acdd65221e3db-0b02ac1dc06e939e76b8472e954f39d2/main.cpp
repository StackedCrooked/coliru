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
        using InterfaceId = std::string;
        using PortId = std::string;
    }
    namespace Server
    {
        using namespace Common;
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
        using Common::PortId;
        using Common::IP;
        using SetIP = Command<void(PortId, IP)>;
        using SetGW = Command<void(PortId, IP)>;
        using SetNM = Command<void(PortId, IP)>;
    }    
    namespace ICMP
    {
        using Common::IP;
        using SetDestination = Command<void(IP)>;
        using SetDataSize = Command<void(int)>;
    }
}


namespace EthernetImpl {
    
    
using namespace Communication::Ethernet;


struct SetMAC_impl : SetMAC
{
    void operator()(const MAC & ) const
    {
    }
};


} // EthernetImpl


namespace IPv4Impl {
    
    
using namespace Communication::IPv4;
    
    
struct SetIP_impl : SetIP
{    
    void operator()(const PortId & , const IP & ) const
    {
    }
};


struct SetGW_impl : SetGW
{
    void operator()(const IP & ) const
    {
    }
};


struct SetNM_impl : SetNM
{
    void operator()(const IP & ) const
    {
    }
};


} // IPv4Impl