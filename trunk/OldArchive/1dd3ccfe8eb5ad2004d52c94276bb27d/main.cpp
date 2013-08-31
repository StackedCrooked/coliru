#include <stdint.h>
#include <cstring>
#include <iostream>
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
    
    IP(Type type = v4);
    
    IP(const std::string & addr);
    
    // Move constructor.
    IP(IP&& rhs) = default;
    
    // Move-assignment operator.
    IP& operator=(IP&&) = default;    
    
    // Copy constructor.
    IP(const IP& rhs);
    
    // Copy-assignment operator.
    IP& operator=(IP rhs_copy)
    {
        using std::swap;
        swap(mImpl, rhs_copy.mImpl);
        return *this;
    }
    
    Type getType() const;
    
    const uint8_t * getData() const;
    
    int getLength() const;
    
private:
    std::unique_ptr<IPImpl> mImpl;
};


//
// Inside IP.cpp file
//
struct IPImpl
{
    virtual std::unique_ptr<IPImpl> clone() const = 0;    
    virtual ~IPImpl() {}    
    virtual const uint8_t * getData() const = 0;
    virtual int getLength() const = 0;
};


// Convenience function for creating unique_ptr objects.
template<typename T, typename ...Args>
std::unique_ptr<T> make_unique(Args&& ...args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}


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


IP::IP(const IP& rhs) :
    mImpl(rhs.mImpl->clone())
{
}


std::unique_ptr<IPImpl> CreateImpl(IP::Type inType)
{    
    switch (inType)
    {
        case IP::v4: return make_unique<IPv4>();
        case IP::v6: return make_unique<IPv6>();
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
    std::cout << port.getIP().getLength() << std::endl;    
    
    IP ip(IP::v6);
    port.setIP(ip);
    std::cout << ip.getLength() << std::endl;    
}
