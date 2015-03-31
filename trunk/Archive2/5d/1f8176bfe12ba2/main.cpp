#include <iostream>

struct Bit 
{
    static const unsigned rawDataCount = 32U;
    unsigned bit:8;   
    unsigned bit1:8;   
} __attribute__((__packed__));
int main()
{
    Bit b;
    std::cout << "size of empty class: "     << sizeof(b)        << std::endl;
}
