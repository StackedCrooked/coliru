#include<stdio.h>
void print(int[5][5]);
void pass(int[5][5],int[5][5]);
int neigh(int,int,int[5][5]);
static int nosofpass;
int main()
{
int a[5][5]={{0,0,0,0,0},{0,0,1,1,0},{0,1,1,0,0},{0,0,1,0,0},{0,0,0,0,0}};
int b[5][5]={{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
printf("enter ur intial cell to get generation patterns\n");
/*for(int i=0;i<5;i++)
{
 for(int j=0;j<5;j++)
 {
  scanf("%d",a[i][j]);
  }
}*/
 print(a);
pass(a,b);
 }

void print(int d[5][5])
{
  for(int i=0;i<5;i++)
   {
    for(int j=0;j<5;j++)
    {
      if(d[i][j]==0)
      printf("-");
      else
      printf("*");
    }
   printf("\n");
  }
}
void pass(int t1[5][5],int t2[5][5])
{
 for(int i=0;i<5;i++)
 {
  for(int j=0;j<5;j++)
  {
  int count1=neigh(i,j,t1);
    if((count1<2)&&(t1[i][j]==1))
    t2[i][j]=0;
    else if((count1>3)&&(t1[i][j]==1))
    t2[i][j]=0;
    else if((count1==3)&&(t1[i][j]==0))
    t2[i][j]=1;
    else if((count1==2)||(count1==3))
    {
     if(t1[i][j]==1)
     t2[i][j]=1;
     else
     t2[i][j]=0;
     }
    else
    t2[i][j]=0;
   }
  }
 print(t2);
 nosofpass++;
  pass(t2,t1);
}
int neigh(int i,int j,int c[5][5])
{
 int count=0;
 int leftn=j-1;
 int rightn=j+1;
 int topn=i-1;
 int bottomn=i+1;
 if(leftn<0)
 leftn=0;
 if(topn<0)
 topn=0;
 if(rightn==5)
 rightn=j;
 if(bottomn==5)
 bottomn=i;
 for(int k=topn;k<=bottomn;k++)
 {
   for(int m=leftn;m<=rightn;m++)
   {
    if(i==k&&j==m)
    continue;
    else if(c[k][m]==0)
    continue;
    else
    count++;
    }
  }
 return(count);
}
