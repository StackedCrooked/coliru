#include <iostream>
#include <cstdint>
#include <arpa/inet.h>


template<int bits, int multiplier = 1>
struct Field
{
    Field() = default;
    
    Field(uint64_t n) : value(n) {}
    
    
    Field& operator=(uint64_t n)
    {
        value = n / multiplier;
        return *this;
    }
    
    operator uint64_t() const
    {
        return value * multiplier;
    }
    
    uint64_t value:bits;
}
__attribute__((packed));


struct Net16
{
    operator uint16_t() const { return htons(n_); }
    Net16& operator=(uint16_t n) { n_ = ntohs(n); return *this; }
    uint16_t n_;
};


struct IPv4Header
{
    Field<4> Version;
    Field<4, 4> IHL;
    Field<8> TOS;
    Net16 TotalLength;
    Net16 Identificiation;
};


static_assert(std::is_pod<IPv4Header>::value, "");
//static_assert(sizeof(IPv4Header) == 20, "");

int main()
{
    IPv4Header header;
    header.Version = 4;
    header.IHL = 20;
    header.TOS = 0;
    
    std::cout
        << " HEADER=" << header.Version
        << " IHL=" << header.IHL
        << " TOS=" << header.TOS
        << std::endl;
}
