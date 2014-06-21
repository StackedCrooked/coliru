
//#include <iostream>
//#include <string>
//#include <cstring>
//#include <vector>
//#include <stdint.h>

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;


uint16_t checksum2(const uint8_t *buf, uint32_t size)
{
    uint64_t sum = 0;
    const uint64_t *b = reinterpret_cast<const uint64_t *>(buf);

    uint32_t t1, t2;
    uint16_t t3, t4;

    /* Main loop - 8 bytes at a time */
    while (size >= sizeof(uint64_t))
    {
        uint64_t s = *b++;
        sum += s;
        if (sum < s) sum++;
        size -= 8;
    }

    /* Handle tail less than 8-bytes long */
    buf = reinterpret_cast<const uint8_t *>(b);
    if (size & 4)
    {
        uint32_t s = *reinterpret_cast<const uint32_t *>(buf);
        sum += s;
        if (sum < s) sum++;
        buf += 4;
    }

    if (size & 2)
    {
        uint16_t s = *reinterpret_cast<const uint16_t *>(buf);
        sum += s;
        if (sum < s) sum++;
        buf += 2;
    }

    if (size)
    {
        uint8_t s = *buf;
        sum += s;
        if (sum < s) sum++;
    }

    /* Fold down to 16 bits */
    t1 = sum;
    t2 = sum >> 32;
    t1 += t2;
    if (t1 < t2) t1++;
    t3 = t1;
    t4 = t1 >> 16;
    t3 += t4;
    if (t3 < t4) t3++;

    return ~t3;
}


uint16_t checksum2(const char* buf, uint32_t size)
{
    return checksum2(reinterpret_cast<const uint8_t*>(buf), size);
}



int main(int argc, char** argv)
{
    auto data = reinterpret_cast<uint8_t*>(argv[1]);
    int size = 0;
    while (data[size]) size++;
    data[0] = 0;
    data[1] = 0;



    uint16_t checksum = checksum2(data, size);

    auto bytes = reinterpret_cast<const uint8_t*>(&checksum);
    data[0] = bytes[0];
    data[1] = bytes[1];

    uint16_t verify = checksum2(data, size);


    return verify;
}
