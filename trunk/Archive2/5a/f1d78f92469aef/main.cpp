#include <stdio.h>

int main(){
  printf("%lu %lu\n",sizeof(int), sizeof(long int));
  unsigned int a = 1 << 32;
  unsigned long int b = 1 << 32;
  printf("%u %lu\n", a, b);
  return 0;
}