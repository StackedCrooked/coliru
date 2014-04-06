#include<stdio.h>
intmain(){
intv[]={20,35,76,80};
int *a;
a=&v[1];
--(*++a);
(*a--)=(*++a)+1;
(*a)=--(*--a);
printf("%d,%d,%d,%d\n",v[0],v[1],v[2],v[3]);
}