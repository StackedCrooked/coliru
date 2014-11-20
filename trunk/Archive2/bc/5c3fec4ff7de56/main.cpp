#include <stdio.h>
 
void func(void) {
  int val = 0;
  /* ... */ 
  size_t s = sizeof(int [++val]);
  printf("%zu, %d\n", s, val);
  /* ... */
}

int main(void) { func(); }
