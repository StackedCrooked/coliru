#include <stdint.h>



uint32_t OnesComplementSum(const uint8_t* inData, int len, uint32_t sum)
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


#ifdef UGLY_LOOP
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
#elif CLEAN_LOOP
    while (len > 32)
    {
        run8();
        run8();
        run8();
        run8();
        len -= 32;
    }
    
    while (len > 8)
    {
        run8();
        len -= 8;
    }
#else
#error WHICH LOOP?
#endif

    sum += (a + b) + (c + d);

    auto reduce = [&] {
        sum = (sum & uint16_t(-1)) + (sum >> 16);
        sum > uint16_t(-1) ? sum -= uint16_t(-1) : sum;
    };

    reduce();

    while ((len -= 2) >= 0) sum += *b16++;

    if (len == -1)
    {
        // Add the last byte
        sum += static_cast<uint16_t>(reinterpret_cast<const uint8_t *>(b16)[0]);
    }

    reduce();

    return sum;
}


#include <iostream>
#include <string>
#include <chrono>

std::string s = "01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789";

#ifdef UGLY_LOOP
const char* loop = "UGLY_LOOP";
#elif CLEAN_LOOP
const char* loop = "CLEAN_LOOP";
#else
#error WHICH LOOP?
#endif

int main()
{
    
    using namespace std::chrono;
    auto start_time = steady_clock::now();
    OnesComplementSum((const uint8_t*)s.data(), s.size(), 0);
    auto elapsed_ns = duration_cast<nanoseconds>(steady_clock::now() - start_time).count();
    
    std::cout << "loop=" << loop << " elapsed_ns=" << elapsed_ns << std::endl;
    
}