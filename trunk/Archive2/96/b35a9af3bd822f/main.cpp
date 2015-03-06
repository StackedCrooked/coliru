#include <iostream>
#include <string>
#include <vector>
#include <regex>

#define MIN(a,b) (((a)<(b))?(a):(b))

void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i=size-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byte = b[i] & (1<<j);
            byte >>= j;
            printf("%u", byte);
        }
    }
    puts("");
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

unsigned int m_unLEDAScanMask = 0x07fc0000;

int main()
{
   
    unsigned int LEDB = 0;
    unsigned int LEDA = 0;
    
    unsigned int unBits = (unsigned int)((100.0f / 100.0f) * 41);
    unsigned int unLEDABits = MIN((unsigned int)32, unBits);
    LEDA = pow(2, unLEDABits) - 1;
    unsigned int unLEDBBits = unBits - unLEDABits;
    LEDB = pow(2, unLEDBBits) - 1;
    printBits(sizeof(LEDA), &LEDA);  
    printBits(sizeof(LEDB), &LEDB);  
    
    int64_t LEDValue = 0;
    LEDValue = LEDB;
    printBits(sizeof(LEDValue), &LEDValue);  
    LEDValue <<= 27;
    printBits(sizeof(LEDValue), &LEDValue);  
    LEDValue |= ((LEDA << 18) & m_unLEDAScanMask);
    printBits(sizeof(LEDValue), &LEDValue);  
}
