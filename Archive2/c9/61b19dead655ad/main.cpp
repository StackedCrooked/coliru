#include<stdio.h>
#include<math.h>

int main()
{
 
  int n,m,a[11],b[11],c[22],temp[11][11];
  int i,j;
  
  do
  {
   scanf("%d%d",&n,&m);
  }while((n<1)||(n>10));
  
  for(i=0;i<=n;i++)
  {
   do
   {
    scanf("%d",&a[n-i]);
   }while((a[n-i]<1) || (a[n-i]>100));
   
  }
 
  for(i=0;i<=m;i++)
  {
   do
   {
    scanf("%d",&b[m-i]);
   }while((b[m-i]<1) || (b[m-i]>100));
   
  }
  
  for(i=0;i<=n;i++)
   for(j=0;j<=m;j++)
    temp[i][j]=a[i]*b[j];
    
  for(i=0;i<=n+m;i++) c[i]=0;
  
  for(i=0;i<=n;i++)
   for(j=0;j<=m;j++)
    c[i+j]+=temp[i][j];
    
  
  printf("%d\n",n+m);
   for(i=0;i<=n+m;i++)
   {
   if(i<n+m) printf("%d ",c[i]);
   else
    printf("%d",c[i]);
   } 
  
   
return 0;
}
  