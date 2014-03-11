#include<stdio.h>
#include<math.h>

float funkcija(int x, int n, float s)
{
    int i=1, f=1,r,b=0;
    double z;
    float q;
    
    do{
          r=2*i-1;
          
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
          
          }while(i<=n);
          
    return s;
    }        

    
    
int main()
{
    int x,n, s=0;
    
    scanf("%d, %d", &x, &n);
    
    s=funkcija(x,n,s);
    
    printf("rjesenje je %f", &s);
    
    scanf("%");
    
    }
    