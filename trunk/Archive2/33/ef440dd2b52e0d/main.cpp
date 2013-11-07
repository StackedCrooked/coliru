#include <stdio.h>
inline int sum(int a, int b) {
  return (a + b);
}

int main()
{
int c;
c = sum(1, 4);
printf("%d\n", c);
// If the compiler inlines the function the compiled code will be the same as writing:
return 0;
}
