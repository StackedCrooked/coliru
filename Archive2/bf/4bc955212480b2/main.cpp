#include <stdint.h>

namespace {

// helper



uint32_t OnesComplementSum(const uint16_t * b16, int len)
{
    uint32_t sum = 0;

    uint32_t a = 0;
    uint32_t b = 0;
    uint32_t c = 0;
    uint32_t d = 0;

    // helper for the loop unrolling
    auto run8 = [&] {
        a += b16[0];
        b += b16[1];
        c += b16[2];
        d += b16[3];
        b16 += 4;
    };

    for (;;) {
        if (len > 32) {
            run8();
            run8();
            run8();
            run8();
            len -= 32;
            continue;
        }

        if (len > 8) {
            run8();
            len -= 8;
            continue;
        }
        break;
    }

    sum += (a + b) + (c + d);
    
    auto reduce = [&]() {
        sum = (sum & 0xFFFF) + (sum >> 16);
        if (sum > 0xFFFF) sum -= 0xFFFF;
    };

    reduce();
    
    while ((len -= 2) >= 0) sum += *b16++;
    
    if (len == -1) sum += *(const uint8_t *)b16; // add the last byte
    
    reduce();
    
    return sum;
}


} // anonymous namespace 


uint32_t get(const uint16_t* data, int length)
{
    return OnesComplementSum(data, length);
}


