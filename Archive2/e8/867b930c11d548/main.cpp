#include <stdio.h>
int main(){
   int n, c=2;
   n=17;
   for(c=2;c<=n-1;c=c+1)
   { if (n%c == 0)
  { printf("%d is not prime. \n",n);
  break;}
   }
   if (n%c != 0)
   printf("%d is prime \n",n);
   return 0;
   }
