#include <cstdint>

int main()
{
    uint32_t i = 0;
    uint32_t count = 1;
    
    while (1)
    {
        if( i < 5 )
            count++;
        
        if (i == 0xFFFFFFFF)
            break;
        i++;
    }

    return count;
}