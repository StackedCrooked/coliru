#include <iostream>
#include <type_traits>
#include <stdexcept>
#include <stddef.h> // offsetoff
#include <stdint.h> // uint8_t, ...
#include <string.h> // memcpy


// extract header field from header data
template<typename T>
T get_field(const uint8_t* b, const uint8_t* e, int offset)
{        
    static_assert(std::is_pod<T>::value, "");  // std::is_trivially_copyable<T> not yet supported by compiler
    
    if (offset + sizeof(T) > e - b)
    {
        throw std::out_of_range("Field out of range.");
    }    
        
    // get data with memcpy, endianness is ignored for now
    
    T t;
    memcpy(&t, b + offset, sizeof(T));
    return t;
}


int main()
{
    // define a network packet type
    struct ICMPv6
    {
        uint8_t type;
        uint8_t code;
        uint16_t checksum;
        uint32_t body;
    };

    // example packet
    ICMPv6 packet = { 1, 2, 3, 4 };

    // obtain begin and end pointers
    auto b = static_cast<const uint8_t*>(static_cast<void*>(&packet));
    auto e = b + sizeof(packet);


    // extract fields, use offsetof to get offset
    int type_value = get_field<uint8_t >(b, e, offsetof(ICMPv6, type));
    int code_value = get_field<uint8_t >(b, e, offsetof(ICMPv6, code));    
    int checksum   = get_field<uint16_t>(b, e, offsetof(ICMPv6, checksum));    
    int body_value = get_field<uint32_t>(b, e, offsetof(ICMPv6, body));
    
    // ^ somewhat generic, but user needs to provide field type and field name
    //   ideally the type should be deducible from the name
    
    
    // check the results
    std::cout << type_value << ' ' << code_value << ' ' << checksum << ' ' << body_value << std::endl;
    

    // 
    // TAKE 2: with macro
    // 

#define GET_FIELD(b, e, HeaderType, FieldName) \
    get_field<decltype(std::declval<HeaderType>().FieldName)>(b, e, offsetof(HeaderType, FieldName))
    
    std::cout
        << (int) GET_FIELD(b, e, ICMPv6, type) << ' '  // we want to print uint8_t as number not as character
        << (int) GET_FIELD(b, e, ICMPv6, code) << ' ' 
        << GET_FIELD(b, e, ICMPv6, checksum) << ' '
        << GET_FIELD(b, e, ICMPv6, body)
        << std::endl;
        
        
        
            
    struct IPv4Header
    {
        // IHL = Internet Header Length: size of IP header including options
        uint8_t  VersionAndIHL; // 0
        uint8_t     TypeOfService; // 1
    
        // Total Length = full header size + payload size
        uint16_t  TotalLength;   // 2
        uint16_t  Identification; // 4
        uint16_t  FlagsAndFragmentOffset; // 6
        uint8_t   TTL; // 8
        uint8_t   Protocol; // 9
        uint16_t  HeaderChecksum; // 10
        uint32_t  SourceAddress; // 12
        uint32_t  DestinationAddress; // 16
    };
    
    IPv4Header ip = IPv4Header();
    ip.VersionAndIHL =  0x40 | (20 / 4);
    
    
    // Usage example: GET_IPv4_FIELD(begin, end, TotalLength)
    #define GET_IPv4_FIELD(b, e, FieldName) \
        GET_FIELD(b, e, IPv4Header, FieldName)
    
    

    // obtain begin and end pointers
    b = static_cast<const uint8_t*>(static_cast<void*>(&ip));
    e = b + sizeof(ip);
    
    
    // minium field size if 8-bit (note that bit fields are not portable)
    uint8_t version_and_ihl = GET_IPv4_FIELD(b, e, VersionAndIHL);
    
    // we still need to bit-fiddle manually to get the 
    auto header_version = version_and_ihl >> 4;
    auto header_length  = 4 * (version_and_ihl & 0x0F);
    
    std::cout << "header_version=" << header_version
              << " header_length=" << header_length
              << std::endl;
}

