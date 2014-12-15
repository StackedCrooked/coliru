#include <stdio.h>

int main () {
   int a;
   unsigned long f,fact(int);
   
   printf("\n Enter a Number : ");
   scanf("%d",&a);
   f=fact(a);
   printf ("\n The Factorial of %d is : %ld",a,f);
   
   return 0;
}

inline unsigned long fact_impl(int b, unsigned long acc) {
    if (b < 0) __builtin_unreachable();
    return __builtin_expect(b < 2, 0) ? acc : fact_impl(b - 1, acc * b);
}

inline unsigned long fact(int a) {
    return fact_impl(a, 1ul);
}