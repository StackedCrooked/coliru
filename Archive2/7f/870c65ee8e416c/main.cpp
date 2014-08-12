#include <limits.h>
#include <stdio.h>

inline int digits(int n) {
  printf("INPUT: %u\n", n);
  int r = 1;
  while (n > 0) {
      n /= 10;
      r++;
  }
  return r;
}

int main() {
  printf("%u\n", digits(UINT_MAX));
  return 0;
}