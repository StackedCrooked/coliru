#include <limits>
#include <cstring>
#include <cstdint>
#include <iostream>

template <class TO, class FROM>
inline TO punning_cast(const FROM &input)
{
    TO out;
    std::memcpy(&out, &input, sizeof(TO));
    return out;
}

int main()
{
    uint32_t i = 0;//std::numeric_limits<uint32_t>::min();
    uint32_t count = 0;
    //return std::numeric_limits<uint32_t>::max();
    do {
    
        float n = punning_cast<float>(i);
        if(n >= 0.0f && n <= 1.0f)
            count++;
         
        
    } while( (i++) != 0xFFFFFFFF ) ;//std::numeric_limits<uint32_t>::max() );
        
    return count;
}