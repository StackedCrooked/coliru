#include<stdio.h>
int main()
{ int n, c = 2; 
 for(n=1;n<=100;n++){
 for ( c = 2 ; c <= n - 1 ; c++ )
 {
 if ( n%c == 0 )
  //printf("%d is not prime.\n", n); questo è un commento?
 {
     break;
 }
 }
 if ( c == n )
 printf("%d ", n);
}
}
 //return 0; posso levare anche questo ed il risultato non cambia, perchè?

