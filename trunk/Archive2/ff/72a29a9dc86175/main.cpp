#include <iostream>
#include <string>
#include <vector>

#include <stdio.h>
#include <math.h>
#define n 100
int main()
{
    int i,j,k,o1=0,o2=0,o3=0,count=0,outcount1=0,outcount2=1,outcount3=0,p,danger=0,d1,d2,d3;
    float t1,t2,t3;
    int a[3],index,min,max;
    
  for(k=1;k<=n;k++)
  {
    count=0;
    for(i=1; i<=k; i++)
    {
     for(j=1; j<=k; j=j+i)
     {
        count++;
        //printf(" Hi count=%d",count);
     }
     //printf("\n");
    }

    t1=(float) k*(log(k)/log(2)); 
    t2=(float) k*k;
    t3=(float) k*sqrt(k);
    //t2= (float) k;
    //t1=(float) k*log(k);
    i= (int) t1;
    j= (int) t2;
    p=(int) t3;
    if(count<i) o1++;
    if(count<j) o2++;
    if(count<p) o3++;
    
    //printf("\n nlogn=%d  ",i);
   if(o1 && o2 && o3)
   {
     a[0]=d1=i-count;
     a[1]=d2=j-count;
     a[2]=d3=p-count;
     
     min=a[0];
     
     printf("\n n=%d, g1(n)=%d, g2(n)=%d, g3(n)=%d, f(n)=%d, g1-f(n)=%d, g2-f=%d, g3-f=%d",k,i,j,p,count,d1,d2,d3);
     
     for(index=1;index<3;index++)
       if(a[index]<min) min=a[index];
          
      if (min==d1)
        outcount1++; 
      else if (min==d2) 
        outcount2++;
      else
        outcount3++;
       
       
   }
   else if( !o1 && !o2 && !o3) danger++;
   else
   {
       if(o1 && o2){
           d1=i-count;
           d2=j-count;
           printf("\n n=%d, g1(n)=%d, g2(n)=%d, f(n)=%d, g1-f=%d, g2-f=%d",k,i,j,count,d1,d2);
           
           if(d1<d2) outcount1++;
           else
             outcount2++;
       }
       else if(o2 && o3){
           d2=j-count;
           d3=p-count;
           printf("\n n=%d, g2(n)=%d, g3(n)=%d, f(n)=%d, g2-f=%d, g3-f=%d",k,j,p,count,d2,d3);
           
           if(d2<d3) outcount2++;
           else
             outcount3++;
       }
       
       else if(o1&&o3){
           d1=i-count;
           d3=p-count;
           printf("\n n=%d, g1(n)=%d, g3(n)=%d, f(n)=%d, g1-f=%d, g3-f=%d",k,i,p,count,d1,d3);
           
           if(d1<d3) outcount1++;
           else
             outcount3++;
       }
       
       else if(o1) {
           printf("\n n=%d, g1(n)=%d, f(n)=%d, g1-f=%d",k,i,count,i-count);
           //outcount1++;
       }
       else if(o2)
       {
           printf("\n n=%d, g2(n)=%d, f(n)=%d, g2-f=%d",k,j,count,j-count);
           //outcount2++;
           
       }
      else if(o3)
       {
           printf("\n n=%d, g3(n)=%d, f(n)=%d, g3-f=%d",k,p,count,p-count);
           //outcount3++;
           
       }
       
   }
   
  }
  
  if(danger<n){
      a[0]=outcount1;
      a[1]=outcount2;
      a[2]=outcount3;
      
      max=0;
      
      for(i=0;i<2;i++) if(a[i]>max) max=a[i];
    
    if(max==outcount1) printf("\n \n loop complexity is O(g1(n)) %d..//",max);
    else  if(max==outcount2)
     printf("\n \n loop complexity is O(g2(n))..  %d  //",max);
    else
          printf("\n \n loop complexity is O(g3(n)).. %d  //",max);
 
  }
  else
    printf("\n given functions does not form an  upper bound  ");
   
  
return 0;
}

    
    
    

