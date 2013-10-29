#include <iostream>

using namespace std;

struct A
{
    static int i;
    A()
    {
        if (i==8) throw 1;

        i++;
        cout << i << " ctr" << endl;

    }
    virtual ~A()
    {
        cout << i << " dtr" << endl;
        i--;
    };
};

int A::i = 0;


int main()
{
    try
    {
        A* aa = new A[10];
        
        aa[0].i = 0;
    }
    catch ( ...)
    {
    }

    cout << A::i;
}