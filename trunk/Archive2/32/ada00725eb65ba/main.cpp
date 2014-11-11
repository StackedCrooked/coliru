#include <iostream>

int main()
{
   for(int i=0;i<10;i++)
      std::cout<< (i&1)<<' '<< ((i&1)^1)<<'\n';
   return 0;
}