#include <math.h>
#include <stdio.h>

inline int magic_number() {
  return round(log10(pow(2, 64))) + 1;
}

int main() {
  int magic = magic_number();
  printf("%d\n", magic);
  return 0;
}