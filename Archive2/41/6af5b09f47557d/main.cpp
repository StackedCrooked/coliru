#include <stdio.h>

int main()
{
   unsigned long a;

   a = 5;
   *(unsigned short *)(void*)&a = 4;
  
  return a;
}