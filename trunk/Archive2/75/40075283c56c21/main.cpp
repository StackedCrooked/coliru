#include<stdio.h>

int fun(int i) {
   printf("%d\n", i);
   if(i<2) {
      return 1;
   } else {
      printf("%d * %d * %d\n", fun(i - 1),  (i - 1), fun(i - 2));
      return fun(i - 1) * (i - 1) * fun(i - 2);
   }   
}

int main() {
   int i = fun(5);
   printf("final = %d", i);
   return 0;
}