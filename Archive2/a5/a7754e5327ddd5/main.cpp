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
        << GET_FIELD(b, e, ICMPv6, body);
        
        
    
}

