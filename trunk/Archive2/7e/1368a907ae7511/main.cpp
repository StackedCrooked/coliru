#include <iostream>
#include <stdio.h>
using namespace std;

int main()
{
    int x[100];
    int y[100];
    int i;
    int j;
    int d;
    cout<<"riempi il vettore x";
    for(i=0;i<100;i++)
    {
        cin>>x[i];}
    i=0;
    j=0;
    d=1;
    while (i<100)
    {
    if(x[i]>0)
    {y[j]=x[i];
    j=j+2;}
    if(x[i]<0)
    {y[d]=x[i];
    d= d+2;
    i=i+1;}
    }
    cout<<"Vettore y:";
    for(i=0;i<100;i++)
    {cout<<y[i];}
    system("pause");
    return 0;
    }
    