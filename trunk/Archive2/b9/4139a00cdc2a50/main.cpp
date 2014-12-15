#include <stdio.h>

int main () {
   int a;
   unsigned long fact(int, unsigned long init = 1ul), f;
   
   printf("\n Enter a Number : ");
   scanf("%d",&a);
   f=fact(a);
   printf ("\n The Factorial of %d is : %ld",a,f);
   
   return 0;
}

unsigned long fact(int b, unsigned long init) {
    return b < 2 ? init : fact(b - 1, init * b);
}
