#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
 
int main()
{
int x = 20;
int *y = x;
 
 
 printf("%d\n",y);
y++;
 
 printf("%d",y);
 
}