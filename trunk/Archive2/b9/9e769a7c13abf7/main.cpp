#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <stdlib.h>

using namespace std;

typedef void function;


auto name="James";
auto age =27;
auto weight=135000;
auto Alive=false;

auto size=256;
auto doit=(size)*(size);
auto numtriangles=doit*2;

int Data[]={1,2,3,4,5,6,7,8,9,10};

int main()
{
    for(auto &x : Data)
    {
       cout<<x<<" ";
    }
    cout<<name<<"\n";
    cout<<age<<"\n";
    cout<<weight<<"\n";
    cout<<Alive<<"\n";
    cout<<size<<"\n";
    cout<<numtriangles<<"\n";

}