#include <array>
#include <cstring>
#include <stdint.h>

void modify(std::array<uint8_t, 128>& blob)
{
    // create helper array of uint32_t objects
    std::array<uint32_t, sizeof(blob)/sizeof(uint32_t)> helper;    
    
    // make sure that the binary size is the same
    static_assert(sizeof(blob) == sizeof(helper), "");
    
    // copy the blob over the helper
    memcpy(&helper[0], &blob[0], sizeof(blob));
    
    // modify the helper
    helper[1] = 42;
    
    // copy helper back over the blob
    memcpy(&blob[0], &helper[0], sizeof(helper));
}

int main()
{
    
}