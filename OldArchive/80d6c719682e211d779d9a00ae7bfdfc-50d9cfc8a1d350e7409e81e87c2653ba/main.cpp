#include <iostream>
using namespace std;
// main() is where program execution begins.
int main()
{
int m,k=0,c=0;
long n;
n=5485;
m=3;
while (n>0)
{
   
   if (m==k) c=n%10;;   
   k++;
   n=n/10;
}
cout<<c;
}