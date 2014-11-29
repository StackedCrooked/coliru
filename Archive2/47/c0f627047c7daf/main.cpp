
struct Internal {};
struct External {};


template<typename ...Protocols>
struct StackImpl;


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
    
    MACAddress  mLocalMAC;
    IPv4Address mLocalIP;
    LocalPort   mLocalPort;
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
    
    MACAddress  mLocalMAC;
    VLANID      mVLANId;
    IPv4Address mLocalIP;
    LocalPort   mLocalPort;
};
