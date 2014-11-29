


struct Stack
{
    // Protocol Identifiers in case of TCP over IPv4
    MAC mLocalMAC;
    IP mLocalIP;
    LocalPort mLocalPort;
};


template<typename ...Protocols>
struct StackImpl;


struct Internal {};
struct External {};


template<>
struct StackImpl<Ethernet, IPv4, TCP>
{
    bool validate(External, Stack& stack, const Packet& packet)
    {
        EthernetDecoder ethdec(packet);
        if (!ethdec.validate() || ethdec.getSourceMAC() != mLocalMAC) return;
        
        IPv4Decoder ipdec(ethdec);    
        if (!ipdec.validate() || ipdec.getSourceIP() != mLocalIP) return;
        
        TCPDecoder tcpdec(dec);
        if (!tcpdec.validate() || tcpdec.getSourcePort() != mLocalPort) return;
    }
    
    MAC mLocalMAC;
    IPv4 mLocalMAC;
    TCP mLocalMAC;
};


template<>
struct StackImpl<Ethernet, VLAN, IPv4, TCP>
{
    bool validate(External, Stack& stack, const Packet& packet)
    {
        EthernetDecoder ethdec(packet);
        if (!ethdec.validate() || ethdec.getSourceMAC() != mLocalMAC) return;
        
        VLANDecoder vlandec(packet);
        if (!vlandec.validate() || vlandec.getVLANID() != mVLANID) return;
        
        IPv4Decoder ipdec(ethdec);    
        if (!ipdec.validate() || ipdec.getSourceIP() != mLocalIP) return;
        
        TCPDecoder tcpdec(dec);
        if (!tcpdec.validate() || tcpdec.getSourcePort() != mLocalPort) return;
    }
    
    MAC mLocalMAC;
    VLANID mVLANID;
    IPv4 mLocalMAC;
    TCP mLocalMAC;
};
