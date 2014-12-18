/* Fibonacci Series c language */
#include<stdio.h>
#include<stdlib.h>
 
 
typedef struct complex complex;

  struct complex
  {
     int re;
     int im;
  };
  
 
complex addition(complex a, complex  b)
{
    complex temp;
    temp.re = a.re + b.re;
    temp.im = a.im + b.im; 
    return temp;
}



int main()
{
    


   return 0;
}