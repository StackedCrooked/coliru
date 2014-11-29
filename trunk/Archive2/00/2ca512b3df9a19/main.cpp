
struct Internal {};
struct External {};


template<typename ...Protocols>
struct Route;


template<>
struct Route<Ethernet, IPv4, TCP>
{
    bool validate(External, const Packet& packet)
    {
        EthernetDecoder ethdec(packet);
        if (!ethdec.validate() || ethdec.getSourceMAC() != mLocalMAC) return false;
        
        IPv4Decoder ipdec(ethdec);    
        if (!ipdec.validate() || mLocalAddresses.has(ipdec.getSourceIP())) return false;
        
        TCPDecoder tcpdec(dec);
        if (!tcpdec.validate() || mLocalPorts.has(tcpdec.getSourcePort())) return false;
    }
    
    MACAddress  mLocalMAC;
    IPv4Address mLocalIP;
    LocalPorts   mLocalPorts;
};


template<>
struct Route<Ethernet, VLAN, IPv4, TCP>
{
    bool validate(External, const Packet& packet)
    {
        EthernetDecoder ethdec(packet);
        if (!ethdec.validate() || ethdec.getSourceMAC() != mLocalMAC) return false;
        
        VLANDecoder vlandec(packet);
        if (!vlandec.validate() || vlandec.getVLANID() != mVLANID) return false;
        
        IPv4Decoder ipdec(ethdec);    
        if (!ipdec.validate() || mLocalAddresses.has(ipdec.getSourceIP())) return false;
        
        TCPDecoder tcpdec(dec);
        if (!tcpdec.validate() || mLocalPorts.has(tcpdec.getSourcePort())) return false;
    }
    
    MACAddress  mLocalMAC;
    VLANID      mVLANId;
    IPv4Address mLocalIP;
    LocalPorts   mLocalPorts;
};



template<>
struct Route<Ethernet, IPv6, TCP>
{
    bool validate(External, const Packet& packet)
    {
        EthernetDecoder ethdec(packet);
        if (!ethdec.validate() || ethdec.getSourceMAC() != mLocalMAC) return false;
        
        IPv6Decoder ipdec(ethdec);    
        if (!ipdec.validate() || mLocalAddresses.has(ipdec.getSourceIP())) return false;
        
        TCPDecoder tcpdec(dec);
        if (!tcpdec.validate() || mLocalPorts.has(tcpdec.getSourcePort())) return false;
    }
    
    MACAddress  mLocalMAC;
    IPv6Addresses mLocalIPs;
    LocalPorts   mLocalPorts;
};


template<>
struct Route<Ethernet, VLAN, IPv6, TCP>
{
    bool validate(External, const Packet& packet)
    {
        EthernetDecoder ethdec(packet);
        if (!ethdec.validate() || ethdec.getSourceMAC() != mLocalMAC) return false;
        
        VLANDecoder vlandec(packet);
        if (!vlandec.validate() || vlandec.getVLANID() != mVLANID) return false;
        
        IPv6Decoder ipdec(ethdec);    
        if (!ipdec.validate() || mLocalAddresses.has(ipdec.getSourceIP())) return false;
        
        TCPDecoder tcpdec(dec);
        if (!tcpdec.validate() || mLocalPorts.has(tcpdec.getSourcePort())) return false;
    }
    
    MACAddress  mLocalMAC;
    VLANID      mVLANId;
    IPv6Addresses mLocalIPs;
    LocalPorts   mLocalPorts;
};



template<>
struct Route<Ethernet, IPv4, UDP>
{
    bool validate(External, const Packet& packet)
    {
        EthernetDecoder ethdec(packet);
        if (!ethdec.validate() || ethdec.getSourceMAC() != mLocalMAC) return false;
        
        IPv4Decoder ipdec(ethdec);    
        if (!ipdec.validate() || mLocalAddresses.has(ipdec.getSourceIP())) return false;
        
        UDPDecoder udpdec(dec);
        if (!udpdec.validate() || mLocalPorts.has(udpdec.getSourcePort())) return false;
    }
    
    MACAddress  mLocalMAC;
    IPv4Address mLocalIP;
    LocalPorts   mLocalPorts;
};


template<>
struct Route<Ethernet, VLAN, IPv4, UDP>
{
    bool validate(External, const Packet& packet)
    {
        EthernetDecoder ethdec(packet);
        if (!ethdec.validate() || ethdec.getSourceMAC() != mLocalMAC) return false;
        
        VLANDecoder vlandec(packet);
        if (!vlandec.validate() || vlandec.getVLANID() != mVLANID) return false;
        
        IPv4Decoder ipdec(ethdec);    
        if (!ipdec.validate() || mLocalAddresses.has(ipdec.getSourceIP())) return false;
        
        UDPDecoder udpdec(dec);
        if (!udpdec.validate() || mLocalPorts.has(udpdec.getSourcePort())) return false;
    }
    
    MACAddress  mLocalMAC;
    VLANID      mVLANId;
    IPv4Address mLocalIP;
    LocalPorts   mLocalPorts;
};



template<>
struct Route<Ethernet, IPv6, UDP>
{
    bool validate(External, const Packet& packet)
    {
        EthernetDecoder ethdec(packet);
        if (!ethdec.validate() || ethdec.getSourceMAC() != mLocalMAC) return false;
        
        IPv6Decoder ipdec(ethdec);    
        if (!ipdec.validate() || mLocalAddresses.has(ipdec.getSourceIP())) return false;
        
        UDPDecoder udpdec(dec);
        if (!udpdec.validate() || mLocalPorts.has(udpdec.getSourcePort())) return false;
    }
    
    MACAddress  mLocalMAC;
    IPv6Addresses mLocalIPs;
    LocalPorts   mLocalPorts;
};


template<>
struct Route<Ethernet, VLAN, IPv6, UDP>
{
    bool validate(External, const Packet& packet)
    {
        EthernetDecoder ethdec(packet);
        if (!ethdec.validate() || ethdec.getSourceMAC() != mLocalMAC) return false;
        
        VLANDecoder vlandec(packet);
        if (!vlandec.validate() || vlandec.getVLANID() != mVLANID) return false;
        
        IPv6Decoder ipdec(ethdec);    
        if (!ipdec.validate() || mLocalAddresses.has(ipdec.getSourceIP())) return false;
        
        UDPDecoder udpdec(dec);
        if (!udpdec.validate() || mLocalPorts.has(udpdec.getSourcePort())) return false;
    }
    
    MACAddress  mLocalMAC;
    VLANID      mVLANId;
    IPv6Addresses mLocalIPs;
    LocalPorts   mLocalPorts;
};

