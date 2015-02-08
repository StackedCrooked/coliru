#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
int main(void)
{
    int n=3;//input signal length
    int m=2;//filter length
    float in[m],x[m+n-1];
    //out[m+n-1];
    //float filter[m],h[n+n-1],y[m+n-1];

    int i=0;
    
    in[0]=3;in[1]=4;in[2]=5;
    //filter[0]=0.2;filter[1]=0.3;
    
        //Create Signal sequence with zero padding
        printf("INPUT SEQUENCE (ZERO-PADDED) \n");
        for(i=0;i<n;i++)
        
        {
           x[i]=in[i];
           printf("x[%d]=%f \n",i,x[i]);
          
        }
        //for(i=n;i<m+n-1;++i)
        //{
         //   x[i]=0;
          //  printf("x[%d]=%f \n",i,x[i]);
}