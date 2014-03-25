#include <stdint.h>
#include <stdio.h>

int main (){
  int i = 142;
  printf ("int= %d, signed char= %d, unsigned char= %d...\n", i, (uint16_t)i, (uint16_t)i);
  return 0;
}