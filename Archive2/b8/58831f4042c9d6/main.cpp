


struct IPv6Address
{   
    unsigned char uint8_t[16];
    
    static constexpr IPv6Address AllNodes = { 0xFF, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 };    
};

