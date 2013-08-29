#include <stdio.h>

typedef int * pint;

int main() {
  printf("Hello from GCC %s\n", __VERSION__);
  printf("siozeof(short) = %ld\n", sizeof(short));
  printf("siozeof(int) = %ld\n", sizeof(int));
  printf("siozeof(long) = %ld\n", sizeof(long));
  printf("siozeof(long long) = %ld\n", sizeof(long long));
  printf("siozeof(long double) = %ld\n", sizeof(long double));
  return 0;
}
