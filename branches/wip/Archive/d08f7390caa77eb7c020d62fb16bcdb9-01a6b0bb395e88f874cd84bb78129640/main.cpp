#include <iostream>
// #include "mytime.hpp"
#include <stdint.h>
#include <ctime>
 
template <class IN>
int32_t
digitTruncate (IN data_in, uint32_t digits, uint64_t* data_out,
               int32_t bits = -1, bool safe = false)
{
  if (bits == -1)
    bits = (digits / 0.3010299957) + 1;
  if (!safe) 
  {
    if (bits > (int32_t)sizeof(data_in) * 8)
      return -1;
  }
  *data_out = (data_in & (0xffffffffffffffff >> (64 - bits)));
  //std::cout << *data_out << std::endl;
  return (bits / 8) + 1;
}
 
int
main()
{
  uint64_t cycles1, cycles2;
  uint32_t out;
  char* block = new char[8];
//  cycles1 = mytime::cycles();
  for (int i = 0; i < 10000; i++)
  {
//    uint32_t init = (uint32_t)mytime::cycles();
    uint32_t init = (uint32_t)std::time(nullptr);
    digitTruncate(init, 5, ((uint64_t*)block), 17, true);
    out = *((uint32_t*)block);
  }
//  cycles2 = mytime::cycles();
//  std::cout << cycles2 - cycles1 << std::endl;
  std::cout << "results: " << out << std::endl;
 
  return 0;
}
