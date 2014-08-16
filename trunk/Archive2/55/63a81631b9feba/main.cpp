#include <iostream>

using namespace std;

template<class T1=int,class T2=int>
class tempex
{
T1 a;
T2 b;
public:
    tempex(T1 x,T2 y)
    {
        a=x;
        b=y;
    }
    void show()
    {
        cout<<"A= \t"<<a<<"\tB=\t"<<b;
    }
};

int main()
{
    tempex <float,int> te1(1.23,123);
    te1.show();
    return 0;
}