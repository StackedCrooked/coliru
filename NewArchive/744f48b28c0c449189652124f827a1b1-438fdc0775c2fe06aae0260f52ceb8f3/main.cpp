#include <iostream>
#include <iomanip>

using namespace std ;

class smartA
{
public:

int *p;
int size;

smartA(){size=10; p = new int [size];}
smartA (int x){size=x; p = new int [x];}
smartA(int y[], int x ){size=x; p = new int [x]; for (int i=0 ; i<x ; i++) p[i]=y[i];}
smartA(const smartA &a) {*this=a;}
~smartA(){delete [] p;}

void displayA()
{
for (int i=0; i<size; i++)
{   cout<<setw(4)<<p[i];
if (((i+1)%5)==0 && i!=0)
cout<<endl;}
    cout<<endl<<endl;
}

void setsmartA(const int a[], int sizea) 
{size=sizea; p = new int[size]; for (int i=0 ; i<size ; i++) p[i]=a[i];}
smartA add(smartA a) ;

};

smartA smartA::add(smartA a)
{
smartA c(a.size+size);

int i=0;
for ( ; i<a.size ;i++)
c.p[i]=a.p[i];

for (int j=0; j<a.size+size; j++, i++)
c.p[i]=p[j];

return c;}

int main()
{
}