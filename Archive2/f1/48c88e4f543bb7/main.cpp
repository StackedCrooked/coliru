#include <iostream>
#include <cstdint>
#include <cstring>

int main ()
{
    uint32_t i = 0xFFAADB11;
    uint8_t c[4];
    uint8_t *p = reinterpret_cast <uint8_t *> (&i);
    memcpy (c, p, 4);
    std::cerr << std::hex << (int)c[0] << " "  << (int)c[1] << " " << (int)c[2] << " " << (int)c[3] << " " << std::endl;
}
