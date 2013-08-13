#include <stdio.h>
//#include <iso646.h>

 int gcd(int x, int y);

 int main()
 {
    int m,n,temp;
    printf("Enter two integers: \n");
    scanf("%d%d",&m,&n);
    printf("GCD of %d & %d is = %d",m,n,gcd(m,n));
    return 0;

  }

 int gcd(int x, int y)
 {
    int i,j,temp1,temp2;

    for(i =1; i <= (x<y ? x:y); i++)
    {
      temp1 = x%i;
      temp2 = y%i;
      if(temp1 ==0 and temp2 == 0)
               j = i;
    } 
    return j;         
 }