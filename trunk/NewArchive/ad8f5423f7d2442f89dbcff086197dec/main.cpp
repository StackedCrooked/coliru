#include <iostream>
using namespace std;
float Gama(int *X[],int n);
int main()
{
    const int n=10;
    int y,z,X[]={8,6,9,6,10,10,9,8,8,9};
    y=Gama(X,n);
    switch(y)
    {
        case 70:
        z=10-y;
        break;
        case 80:
        z=y+10;
        break;
        default:
        z=(y!=60)?(y+20):(y-20);
    }
    std::cout<<"y="<<y<<endl<<"z="<<z<<std::endl;
    return 0;
}
float Gama(int X[],int n)
{
    double r=0;
    int*pi,i;
    pi=&X[0];
    for(int i=0,i<n-5,i++)
    r=r+(*(pi+i));
    return r;
}