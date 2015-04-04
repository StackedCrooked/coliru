#include <stdint.h>


namespace {


// helper
void Reduce(uint32_t & sum)
{

    sum = (sum & 0xFFFF) + (sum >> 16);
    if (sum > 0xFFFF)
    {
        sum -= 0xFFFF;
    }
}


uint32_t OnesComplementSum(const uint8_t * data, int len)
{
    uint32_t sum = 0;

    // incoming data has 2-byte alignment
    const uint16_t* b16 = static_cast<const uint16_t *>(static_cast<const void*>(data));

    uint32_t a = 0;
    uint32_t b = 0;
    uint32_t c = 0;
    uint32_t d = 0;

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

        if (len > 16) {
            run8();
            run8();
            len -= 16;
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

    Reduce(sum);

    while ((len -= 2) >= 0) {
        sum += *b16++;
    }

    // Add the last byte
    if (len == -1) {
        sum += static_cast<uint16_t>(reinterpret_cast<const uint8_t *>(b16)[0]);
    }

    Reduce(sum);
    
    return sum;
}


} // anonymous namespace 



uint32_t get(const uint8_t* data, int length)
{
    return OnesComplementSum(data, length);
}


