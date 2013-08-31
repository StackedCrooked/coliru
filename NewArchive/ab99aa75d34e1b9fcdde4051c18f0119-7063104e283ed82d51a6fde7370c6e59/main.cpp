#include <array>
#include <cstring>
#include <stdint.h>

void modify(std::array<uint8_t, 128>& blob)
{
    uint32_t n;
    memcpy(&n, &blob[4], sizeof(n));
    n = 42;
    memcpy(&blob[4], &n, sizeof(n));
}

int main()
{
    
}