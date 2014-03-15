#include <iostream>
#include <cstdint>

int main()
{
   const uint64_t x = 123456789123456789ULL;
   
   // Pack into uint32_t[2]
   uint32_t ar[2] = {};
   ar[0] = x >> 32;
   ar[1] = x & 0xFFFF;
   
   // Unpack into uint64_t
   uint64_t y;
   y = ar[0];
   y = (y << 32) + ar[1];
   
   // The output should be the same!
   std::cout << x << ' ' << y;
}

