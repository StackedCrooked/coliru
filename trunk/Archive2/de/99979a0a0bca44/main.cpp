#include <stdio.h>
#include <stdlib.h>

int main (void){

int *prout = 2;

printf("%d", prout);
scanf("%d", &prout);
printf("%d", prout);

return 0;
}