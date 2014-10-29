#include <stdio.h>
int main() {
  int a=33,b=22;
  a>b?a:b=222;
  printf("a == %d; b == %d\n", a, b);
  return 0;
}
