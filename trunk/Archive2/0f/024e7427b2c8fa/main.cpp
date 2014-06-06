#include<iostream>
using namespace std;


long double abso (long double x)
{
    return (x > 0 ? x : -x);
}

int main()
{
    long double y=0,x=0;

    for (register long double n=0; y<=0 ;)
    {
        n++;
        y = 0.001 - (1/x);
        x=n;
    };
    cout<< "The number is "<< x <<'\n';
}