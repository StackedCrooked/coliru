#include<stdio.h>
int main()
{ int n, c = 2;
n=17; // numero da testare
for ( c = 2 ; c <= n - 1 ; c++ ) // si cercano divisori
{
if ( n%c == 0 ) // % resto divisione intera
{
printf("%d is not prime.\n", n); // se trovato esci
break;
}
}
if ( c == n ) // se il divisore è uguale al numero: OK
printf("%d is prime.\n", n);
return 0;
}
