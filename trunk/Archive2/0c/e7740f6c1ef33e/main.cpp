#include<stdio.h>
#include<math.h>
int main()
{
    int x,n, i=1, b=0;
    double z;
    float q,s;
    
    scanf("%d,%d", &x, &n);
    
    do{
                   int r=2*i-1, f=1;
                   z=pow(x,r);
                   
                   do{
                              f=f*r;
                              r--;
                              }while(r>0);
                              
                   q=(float)z/f;
                   b++;
                   
                   if(b%2==0)
                   {
                             s=s-q;
                             }
                   else
                   {
                       s=s+q;
                       }
                   i++;
                   
                   }while(i<n);
    
    printf("rjesenje je %f", s);
    scanf("%");
    }
