#include <iostream>
#include <cinttypes>

int main()
{
   unsigned int b = 100000;
   std::cout << (b>>b) << std::endl ;
  
   uint64_t c = 100000;
   std::cout << (c>>c) << std::endl ;
  
   return 0;
}