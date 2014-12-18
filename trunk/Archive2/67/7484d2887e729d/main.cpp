/* Fibonacci Series c language */
#include<stdio.h>
 
 int Fibonacci(int n);
int main()
{
   int n, c;
 
   printf("Enter the number of terms\n");
//   scanf("%d",&n);
    n = 10;
 
   printf("First %d terms of Fibonacci series are :-\n",n);
 
   for ( c = 0 ; c < n; c++ )
   {
      
      printf("fibonnacci de  %d = %d\n",c,Fibonacci(c));
   }
 
   return 0;
}


int Fibonacci(int n)
{
    int i, f_n = 0, f_n_1 = 1, temp;
    if( n == 0)
        return 0;
    else
    
    for(i = 1; i < n; i++)
    {
       temp = f_n;
       f_n += f_n_1;
       f_n_1 = temp;
    }
    return f_n;
}