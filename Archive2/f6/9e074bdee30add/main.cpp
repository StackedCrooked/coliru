#include<stdio.h> 
int main(){ 
int a[]={2,19,2,3,6}; 
int b[]={1,2,3}; 
int *p[2]; 
p[0]=a; 
p[1]=&b[0] + 1; 
printf("%d",p[1][1]); 


} 