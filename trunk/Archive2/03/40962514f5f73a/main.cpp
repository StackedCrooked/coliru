#include<stdlib.h>
#include<stdio.h>

int pgcd(int n, int m)//fonction de base
{
    int r;
    r=n;
    while(r!=0)
    {
        r=n%m;
        if(r!=0)
        {
            n=m;
            m=r;
        }
    }
    return m;
}


int pgcd_rec(int n, int m)//fonction recursive
{
    if(n%m==0)return m;
    else
    {
        return pgcd_rec(m,n%m);
    }
}

int main()
{
 printf("%d et %d",pgcd(5,6),pgcd_rec(5,6));
 return 0;   
}