#include<stdio.h>

int n;
int k;

void printer(int, int);

int main()
{
    scanf("%d", &n);
    k=n;
    if(n%2==0)
    {
       k=n-1;
       printer(n/2,n/2);
    }
    else
    {
      k=n;
      printer(n/2+1, n/2+1);
    }
    return 0;
}

void printer(int i, int j)
{
    for(int l=1; l<=k; l++)
    {
        if(l==i||l==j) printf("*");
        else printf("-");
    }
    printf("\n");
    if(i!=1) printer(i-1, j+1);
    if((n%2==0&&i==1)||(i!=1))
   {
      for(int l=1; l<=k; l++)
      {
         if(l==i||l==j) printf("*");
         else printf("-");
      }
      printf("\n");
   }
}