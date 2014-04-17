#include<iostream.h>
#include<math.h>
void main()
{
int x[5][5],i,j;
for(i=1;i<=4;i++)
for(j=1;j<=4;j++)
x[i][j]=((pow(j,2)+(3*j))/2)+(i-1)*j;
cout<<"\n\n";
for(i=1;i<=4;i++)
{
for(j=1;j<=4;j++)
cout<<x[i][j]<<"\t";
cout<<"\n";
}
}