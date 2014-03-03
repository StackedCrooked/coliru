#include<stdio.h>

int sum=0;
int fun(int n)
{
    if (n == 1)
        return 1 ;
    else
        sum = sum + fun(n - 1) ;

    return sum;
}

int main()
{ 
   printf("%d\n", fun(5) ) ;

   return 0;
}
