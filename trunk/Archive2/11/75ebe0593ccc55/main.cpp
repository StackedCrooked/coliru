


struct IPv6Address
{   
    // We would like to provide the standard multicast addresses.
    // See http://www.iana.org/assignments/ipv6-multicast-addresses/ipv6-multicast-addresses.xhtml
    
    // (1) use static member variables?
    static const IPv6Address AllNodes; // must initialize in cpp file
    
    
    // (2) or use static methods?
    static IPv6Address AllNodes() 
    {
        return { 0xFF, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 };
    }
    
    // (3) or something else?
};
