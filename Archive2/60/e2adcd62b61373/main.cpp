#include <stdio.h>

int main(void){
 static   st;
 auto     au;
 register reg;
 volatile vl;
 const    cn;
 
 printf( "done %zu\n", sizeof(const)) ;
 
   return 0;
}
