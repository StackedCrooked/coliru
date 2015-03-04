extern void bar(void);

void foo(int *x)
{
  int y = *x;  /* (1) */
  if(!x)       /* (2) */
  {
    return;    /* (3) */
  }
  bar();
  return;
}

#include <stddef.h>
#include <stdio.h>

int main() {
    foo(NULL);
    puts("Hello!");
}