#include <stdint.h>
#include <iostream>
#include <type_traits>


// - Value semantics: it behaves like an 'int' (copy generates unique obj).
// - No need to implement copy constructor, copy assignment or destructor.
// - Much faster than other solutions (allocation on stack, no pointer indirections, no virtual function calls).
// - The code is easier to understand than the other solutions.
// - Object size is 20 bytes. (Polymorphic IPv4 and IPv6 were 16 and 24 bytes respectively.)
class  IP
{
public:
    enum Type { v4, v6 };    
    
    explicit IP(Type inType = v4) : mType{inType}, mData{} { }
       
    const uint8_t * getData() const { return mData; }    
    
    int getLength() const { return mType == v4 ? 4 : 16; }
    
private:
    Type mType;
    uint8_t mData[16];
};


//
// User code
//
class Port
{
public:
    void setIP(const IP & inIP) { mIP = inIP; } // natural copy semanics

    const IP & getIP() const { return mIP; }

private:
    IP mIP; // no need to use pointer
};


int main()
{
    std::cout << "IP size: " << sizeof(IP) << std::endl;
    std::cout << "IP alignment: " << std::alignment_of<IP>::value << std::endl;
    
    Port port;
    std::cout << "Our IP now has length: " << port.getIP().getLength() << std::endl;    
    
    IP ip(IP::v6);
    port.setIP(ip);
    std::cout << "Our IP now has length: " << port.getIP().getLength() << std::endl;
}
