#include <cstdint>
#include <memory>
#include <string>


struct Packet {};


struct Stack
{   
    enum : std::uint64_t
    {
        VLAN     = 1 << 1,
        IPv4     = 1 << 2,
        IPv6     = 1 << 3,
        TCP      = 1 << 4,
        UDP      = 1 << 5
    };
    
    
    // bitmask tells me which protocols I have
    std::uint64_t mProtocols = 0; 
    
    void pop(const Packet& packet)
    {
        // local copy
        auto protocols = mProtocols;
        
        switch (protocols & 0x7)
        {
            case IPv4 | TCP:
            case IPv4 | TCP | UDP:
            {
                EthernetDecoder ethdec(packet);
                if (!ethdec.isValid())
                {
                    return;
                }
                
                switch (ethdec.getEtherType())
                {
                    case EtherType::IPv4: break;
                    case EtherType::ARP: handle(ARPDecoder(ethdec), ethdec); return;
                    default: { LOG(Warning) << "Unexpected ethertype: " << ethdec.getEtherType(); return; }
                }
            
                IPv4Decoder ipdec(ethdec);
                if (!ipdec.isValid())
                {
                    return;
                }
                
                switch (ipdec.getProtocol())
                {
                    case IPProtNum::TCP: break;
                    case IPProtNum::UDP: handle(UDPDecoder(ethdec), ethdec); return;
                    default: { LOG(Warning) << "Unexpected protocol number: " << ipdec.getProtocol(); return; }
                }
                
                TCPDecoder tcpdec(ipdec);
                if (!tcpdec.isValid(ipdec))
                {
                    return;
                }
                
                mImpl->pop(tcpdec, ipdec, ethdec);
                
                break;
            }
            case IPv6 | TCP:
            case IPv6 | TCP | UDP:
            {
                EthernetDecoder ethdec(packet);
                if (!ethdec.isValid())
                {
                    return;
                }
                
                switch (ethdec.getEtherType())
                {
                    case EtherType::IPv6: break;
                    case EtherType::ARP: handle(ARPDecoder(ethdec), ethdec); return;
                    default: { LOG(Warning) << "Unexpected ethertype: " << ethdec.getEtherType(); return; }
                }
            
                IPv6Decoder ipdec(ethdec);
                if (!ipdec.isValid())
                {
                    return;
                }
                
                switch (ipdec.getProtocol())
                {
                    case IPProtNum::TCP: break;
                    case IPProtNum::UDP: handle(UDPDecoder(ethdec), ethdec); return;
                    default: { LOG(Warning) << "Unexpected protocol number: " << ipdec.getProtocol(); return; }
                }
                
                TCPDecoder tcpdec(ipdec);
                if (!tcpdec.isValid(ipdec))
                {
                    return;
                }
                
                mImpl->pop(tcpdec, ipdec, ethdec);
                
                break;
            }
            case VLAN | IPv4 | TCP:
            case VLAN | IPv4 | TCP | UDP:
            {
                // ...
                break;
            }
            case VLAN | IPv6 | TCP:
            case VLAN | IPv6 | TCP | UDP:
            {
                // ...
                break;
            }
            default:
            {
                // slow path
            }
        };
    }
    
    struct Impl
    {
        template<typename ...Dec>
        void pop(Dec&& ...)
        {
        }
    };
    
    std::shared_ptr<Impl> mImpl;
};


int main()
{
}





struct EthernetDecoder
{
    bool isValid() const { return true; }
    bool isIPv4() const { return true; }
    int getEtherType() const { return IPv4; }
};


struct VLANDecoder
{
    bool isValid() const { return true; }
    bool isIPv4() const { return true; }
    int getEtherType() const { return IPv4; }
};


struct IPv4Decoder
{
    bool isValid() const { return true; }
    bool isTCP() const { return true; }
    int getProtocol() const { return TCP; }
};


struct IPv6Decoder
{
    bool isValid() const { return true; }
    bool isTCP() const { return true; }
    int getProtocol() const { return TCP; }
};


struct TCPDecoder
{
    bool isValid(const IPv4Decoder&) const { return true; }
    bool isValid(const IPv6Decoder&) const { return true; }
};