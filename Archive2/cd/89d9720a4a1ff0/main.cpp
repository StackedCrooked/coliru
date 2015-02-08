#include <stdio.h>

typedef struct
{
   int a, b, c;
} T;

int main()
{
   T t1 = {0};
   printf("%d,%d,%d\n", t1.a, t1.b, t1.c);
   
   T t2 = {};
   printf("%d,%d,%d\n", t2.a, t2.b, t2.c);
}