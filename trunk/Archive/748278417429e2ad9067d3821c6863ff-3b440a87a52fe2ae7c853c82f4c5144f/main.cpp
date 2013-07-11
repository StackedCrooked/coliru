#include<stdio.h>
void main(){
int a1[] = {1,2,3,4,5,6};
int a2[] = {7,8,9,10,11,12};
int *a3 = a1;
int *a4 = a2;
int **a[2];
a[0] = a3;
a[1] = a4;

printf("%d",*(++(*a)));



}