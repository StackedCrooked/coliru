#include <stdio.h>

void f(int x)
{
    printf("f(%d)\n", x);
}

int main()
{
  f({{1}}); // f(A(1)) should be printed, not f(1)
}
