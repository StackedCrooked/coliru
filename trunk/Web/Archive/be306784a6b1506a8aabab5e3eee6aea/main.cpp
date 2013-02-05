#include <stdint.h>
#include <cstring>
#include <memory>


class IP
{
public:
    virtual std::unique_ptr<IP> clone() const = 0;
    
    typedef uint8_t Byte;
    Byte getByte(int index) const { return getData()[index]; };  
    void setByte(int index, Byte b) { getData()[index] = b; }
    Byte * getData() { return const_cast<Byte*>(static_cast<const IP&>(*this).getData()); }
    virtual const Byte * getData() const = 0; 
    virtual int getLength() const = 0;
};

inline bool operator==(const IP & lhs, const IP & rhs)
{
    return lhs.getLength() == rhs.getLength() && !memcmp(lhs.getData(), rhs.getData(), lhs.getLength());
}

class IPv4 : public IP
{
public:
    virtual std::unique_ptr<IP> clone() const
    {
        return std::unique_ptr<IP>(new IPv4(*this));
    }
    
    IPv4() : data_() {}
    virtual const Byte * getData() const { return data_; }
    int getLength() const { return sizeof(data_); }

private:
     Byte data_[4];
};

class IPv6 : public IP
{
public:
    virtual std::unique_ptr<IP> clone() const
    {
        return std::unique_ptr<IP>(new IPv6(*this));
    }
    
    IPv6() : data_() {} 
    virtual const Byte * getData() const { return data_; } 
    int getLength() const { return sizeof(data_); } 

private:
    Byte data_[16];
};


class Port
{
public:
    void setIP(const IP & inIP) { mIP = inIP.clone(); }

    const IP & getIP() const { return *mIP; }

private:
    std::unique_ptr<IP> mIP;
};


int main()
{
    Port port;
    port.setIP(IPv4());
    port.getIP().getByte(0);
}
