#include <stdio.h>

int main(){
  int shift = 31;
  unsigned long int b = 1LU << shift; /* or 1U << shift */
  printf("%lu\n", b);
  return 0;
}
