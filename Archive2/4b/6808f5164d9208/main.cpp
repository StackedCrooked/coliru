#include<stdio.h>


main()
{
   int x = 10, y = -8, z =5, p, q , r;

   p = --x * y++ - ++z;
   q = x % 7;
   r = p++ * --q;

   printf("p = %d\n", p);
   printf("q = %d\n", q);
   printf("r = %d\n", r);




}