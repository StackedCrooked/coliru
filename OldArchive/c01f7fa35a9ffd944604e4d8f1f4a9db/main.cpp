#include <stdint.h>
#include <cstring>
#include <iostream>
#include <memory>
#include <stdexcept>


// BRIDGE PATTERN
    

// Forward declaration for the IP implementation object.
namespace Detail { struct IPImpl; }


// IP represents an IPv4 or IPv6 address.
class IP
{
public:
    enum Type { v4, v6 }; 
    
    IP(Type type = v4);    
    
    // Copy constructor.
    IP(const IP&);       
    
    // Copy-assignment operator.
    IP& operator=(IP);
    
    Type getType() const;
    
    const uint8_t * getData() const;
    
    int getLength() const;
    
private:
    std::unique_ptr<Detail::IPImpl> mImpl;
};


//
// Inside IP.cpp file
//
namespace Detail {


// Convenience function for creating unique_ptr objects.
template<typename T, typename ...Args>
std::unique_ptr<T> make_unique(Args&& ...args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
  
  
struct IPImpl
{
    // Factory method that creates an IPv4 or IPv6 object.
    static std::unique_ptr<IPImpl> Create(IP::Type inType);    
    
    virtual ~IPImpl() {}    
    virtual std::unique_ptr<IPImpl> clone() const = 0;
    virtual const uint8_t * getData() const = 0;
    virtual int getLength() const = 0;
};


struct IPv4 : IPImpl
{    
    IPv4() : data_() {}
    virtual std::unique_ptr<IPImpl> clone() const { return make_unique<IPv4>(*this); }
    const uint8_t * getData() const { return data_; }
    int getLength() const { return sizeof(data_); }
    uint8_t data_[4];
};


struct IPv6 : IPImpl
{
    IPv6() : data_() {} 
    virtual std::unique_ptr<IPImpl> clone() const { return make_unique<IPv6>(*this); }
    const uint8_t * getData() const { return data_; } 
    int getLength() const { return sizeof(data_); } 
    uint8_t data_[16];
};


std::unique_ptr<IPImpl> IPImpl::Create(IP::Type inType)
{    
    if (inType == IP::v4) return make_unique<IPv4>();
    if (inType == IP::v6) return make_unique<IPv6>();
    throw std::logic_error("Invalid IP type.");
}


} // namespace Detail


IP::IP(const IP& rhs) :
    mImpl(rhs.mImpl->clone())
{
}


IP::IP(Type inType) :
    mImpl(Detail::IPImpl::Create(inType))
{
}


IP& IP::operator=(IP rhs_copy)
{
    using std::swap;
    swap(mImpl, rhs_copy.mImpl);
    return *this;
}


IP::Type IP::getType() const
{
    return dynamic_cast<Detail::IPv4*>(mImpl.get()) ? v4 : v6;
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
    std::cout << port.getIP().getLength() << std::endl;    
    
    IP ip(IP::v6);
    port.setIP(ip);
    std::cout << ip.getLength() << std::endl;    
}
