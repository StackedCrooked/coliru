#include <stdint.h>
#include <cstring>
#include <iostream>
#include <memory>
#include <stdexcept>


// SOLUTION 3: Value semantics.
//
// Properties:
// - Behaves like built-in types (copy generates a unique object).
// - No pointer indirections.
// - No inheritance.
// - Very simple.
//
// Score: 10/10.
    

class  IP
{
public:
    enum Type { v4, v6 };
    
    IP(Type inType = v4) : mType(inType), mData() { }
       
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
    void setIP(const IP & inIP) { mIP = inIP; }

    const IP & getIP() const { return mIP; }

private:
    IP mIP;
};


int main()
{
    Port port;
    std::cout << port.getIP().getLength() << std::endl;    
    
    IP ip(IP::v6);
    port.setIP(ip);
    std::cout << ip.getLength() << std::endl;    
}
