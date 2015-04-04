#include "Config.h"
#include "Terrible/Stack/Checksum16.h"
#include <iostream>


namespace Terrible {
namespace Stack {
namespace Detail {
namespace {


// Helper function for the 16-bit checksum
inline void Reduce(uint32_t & sum)
{
    sum = (sum & uint16_t(-1)) + (sum >> 16);
    sum > uint16_t(-1) ? sum -= uint16_t(-1) : sum;
}


inline uint32_t OnesComplementSumImpl(const uint8_t * inData, int len, uint32_t sum)
{
    const uint16_t * b16 = reinterpret_cast<const uint16_t *>(inData);

    uint32_t a = 0, b = 0, c = 0, d = 0;

    auto run8 = [&]{
        a += b16[0];
        b += b16[1];
        c += b16[2];
        d += b16[3];
        b16 += 4;
    };

    for (;;)
    {
        if (len > 32)
        {
            run8();
            run8();
            run8();
            run8();
            len -= 32;
            continue;
        }

        if (len > 8)
        {
            run8();
            len -= 8;
            continue;
        }

        break;
    }

    sum += (a + b) + (c + d);

    Reduce(sum);

    while ((len -= 2) >= 0)
    {
        sum += *b16++;
    }

    if (len == -1)
    {
        // Add the last byte
        sum += static_cast<uint16_t>(reinterpret_cast<const uint8_t *>(b16)[0]);
    }

    Reduce(sum);

    return sum;
}


inline Net16 CheckSum16Impl(const uint8_t* data, int length)
{
    uint32_t sum = OnesComplementSumImpl(data, length, 0);
    return { static_cast<uint16_t>(~sum & 0xFFFF) };
}


} } // namespace Detail::anonymous namespace


uint32_t OnesComplementSum(const uint8_t * inData, int inLength, uint32_t intermediate_result)
{
    return Detail::OnesComplementSumImpl(inData, inLength, intermediate_result);
}


uint32_t OnesComplementSum(const void* inData, int len, uint32_t intermediate_result)
{
    return Detail::OnesComplementSumImpl(static_cast<const uint8_t*>(inData), len, intermediate_result);
}


Net16 CheckSum16(const uint8_t* data, int length)
{
    return Detail::CheckSum16Impl(data, length);
}


Net16 CheckSum16(const void* inData, int inLength)
{
    return Detail::CheckSum16Impl(static_cast<const uint8_t*>(inData), inLength);
}


Net16 CheckSum16(const uint8_t* b, const uint8_t* e)
{
    return Detail::CheckSum16Impl(b, e - b);
}


} } // namespace Terrible::Stack

