#include <stdio.h>

void f(int **const p); 

int main() 
{ 
   int i = 10; 
   int *p = &i; 
   f(&p); 
   printf("%d ", *p); 
   printf("%d ", *p); 
} 

void f(int **const p) 
{ 
   int j = 11; 
   *p = &j; 
   printf("%d ", **p); 
}