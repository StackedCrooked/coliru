#include <stdint.h>
#include <cstring>
#include <iostream>
#include <memory>


// SOLUTION 1: Clone method.
//
// Properties:
// - User must store IP object as (smart) pointer.
// - Copy is provided via virtual clone method.
// - Vtable increases object size.
// - Virtual dispatch may hurt performance.
//
// Score: 6/10


// Convenience function for creating unique_ptr objects.
template<typename T, typename ...Args>
std::unique_ptr<T> make_unique(Args&& ...args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}


class IP
{
public:
    virtual std::unique_ptr<IP> clone() const = 0;    
    virtual const uint8_t * getData() const = 0;     
    virtual int getLength() const = 0;
};


class IPv4 : public IP
{
public:    
    IPv4() : data_() {}    
    virtual std::unique_ptr<IP> clone() const { return make_unique<IPv4>(*this); }    
    virtual const uint8_t * getData() const { return data_; }    
    int getLength() const { return sizeof(data_); }

private:
     uint8_t data_[4];
};


class IPv6 : public IP
{
public:    
    IPv6() : data_() {} 
    virtual std::unique_ptr<IP> clone() const { return make_unique<IPv6>(*this); }
    virtual const uint8_t * getData() const { return data_; } 
    int getLength() const { return sizeof(data_); } 

private:
    uint8_t data_[16];
};


class Port
{
public:
    Port() : mIP(make_unique<IPv4>()) {}
    
    void setIP(const IP & inIP) { mIP = inIP.clone(); }    
    const IP & getIP() const { return *mIP; }

private:
    std::unique_ptr<IP> mIP;
};


int main()
{
    Port port;
    std::cout << port.getIP().getLength() << std::endl;
    
    IPv6 ip6;
    port.setIP(ip6);
    
    const IP & ip = port.getIP();
    std::cout << ip.getLength() << std::endl;
}
