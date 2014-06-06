#include<iostream>
using namespace std;

int main()
{
 long abs(long x)
 {
    return (x > 0 ? x : -x);
 };

 long y=0,x=0,a=0,b=0;

 for (register long n=1; y<0 ;n++)
 {
    y = - abs ((1/n) - a ) + b;
 };
 cout<< "The number is "<< y <<'\n';
}