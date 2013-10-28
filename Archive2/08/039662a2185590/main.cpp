#include <iostream>
#include <cinttypes>

int main()
{
   unsigned int b = 100000;
   std::cout << (b>>b) << std::endl ;

   return 0;
}