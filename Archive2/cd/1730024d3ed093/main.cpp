#include <iomanip>
#include <iostream>
#include <type_traits>


struct Flagger
{
    Flagger(std::ostream& os) : os(os), flags(os.flags()) {}
    Flagger(const Flagger&) = delete;    
    Flagger& operator=(const Flagger&) = delete;
    ~Flagger() { os.flags(flags); }
    std::ostream& os;
    std::ios_base::fmtflags flags;
};


struct Byte
{
    friend std::ostream& operator<<(std::ostream& os, Byte b)
    {
        return os << static_cast<int>(b.value_);
    }
    
    unsigned char value_;
};


struct MAC
{
    friend std::ostream& operator<<(std::ostream& os, MAC mac)
    {   
        Flagger flagger(os);
        
        os << std::hex;
        
        for (auto& b : mac.bytes)
        {
            os << (&b == mac.bytes ? "" : ":") << std::setw(2) << std::setfill('0') << b;
        }
        return os;
    }
    
    Byte bytes[6];
};


struct IP
{
    friend std::ostream& operator<<(std::ostream& os, IP ip)
    {
        Flagger flagger(os);
        
        os << std::dec;
        
        for (auto& b : ip.bytes)
        {
            os << (&b == ip.bytes ? "" : ".") << b;
        }
        return os;
    }
    
    Byte bytes[4];
};


int main()
{
    std::cout << MAC{ 0x00, 0xff, 0x23, 0x00, 0x00, 0x01 } << std::endl;
    std::cout << IP{ 10, 0, 0, 1 } << std::endl;
}

