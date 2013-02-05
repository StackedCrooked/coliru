#include <stdint.h>
#include <cstring>
#include <memory>
#include <stdexcept>
    

// Forward declaration to the impl object.
struct IPImpl;


// This class represents an internet address.
// Bridge pattern replaces inheritance with composition.
// 
class IP
{
public:
    enum Type { v4, v6 };
    
    IP();
    
    IP(Type type);
    
    IP(const std::string & addr);
    
    Type getType() const;
    
    const uint8_t * getData() const;
    
    int getLength() const;
    
private:
    std::shared_ptr<IPImpl> mImpl;
};


//
// Inside IP.cpp file
//
struct IPImpl
{
    virtual ~IPImpl() {}    
    virtual const uint8_t * getData() const = 0;
    virtual int getLength() const = 0;
};


struct IPv4 : IPImpl
{    
    IPv4() : data_() {}
    const uint8_t * getData() const { return data_; }
    int getLength() const { return sizeof(data_); }
    uint8_t data_[4];
};


struct IPv6 : IPImpl
{
    IPv6() : data_() {} 
    const uint8_t * getData() const { return data_; } 
    int getLength() const { return sizeof(data_); } 
    uint8_t data_[16];
}; 


std::shared_ptr<IPImpl> CreateImpl(IP::Type inType)
{    
    switch (inType)
    {
        case IP::v4: return std::make_shared<IPv4>();
        case IP::v6: return std::make_shared<IPv6>();
        default:
        {
            struct InvalidIPType : std::logic_error
            {
                InvalidIPType() : std::logic_error("InvalidIPType") {}
                ~InvalidIPType() throw() {}
            };
            throw InvalidIPType();
        }
    }
}


IP::IP() :
    mImpl(CreateImpl(v4))
{
}


IP::IP(Type inType) :
    mImpl(CreateImpl(inType))
{
}


IP::IP(const std::string & ) :
    mImpl(CreateImpl(v4)) // dummy impl
{
}


IP::Type IP::getType() const
{
    return dynamic_cast<IPv4*>(mImpl.get()) ? v4 : v6;
}

  
const uint8_t * IP::getData() const
{
    return mImpl->getData();
}        


int IP::getLength() const
{
    return mImpl->getLength();
}   


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
    IP ip("1.2.3.4");
    port.setIP(ip);
}
