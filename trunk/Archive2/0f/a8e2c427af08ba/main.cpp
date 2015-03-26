#include <iostream>
#include <string>
#include <cstring>
using namespace std;
int main()
{int r,i,min,z,in,t,k,c;
char s[256];
r=strlen(s);
cin.getline(s,256);
k=1;c=0;in=0;t=0;z=1;
for (i=0;i<r;i++)
{if (s[i]==' ' || i==r-1)
{if (k==1)
{min=t;
k=2;}
if (i==r-1)
t=t+1;
z=1;
if (min>t)
{min=t;
c=in;}
cout<<c;
t=0;}
else
{t=t+1;
if (z==1)
{in=i;
z=2;}}}
cout<<c; 
for (i=c;i<r;i++)
cout<<s[i];
return 0;}
