#include <iostream>

using namespace std;

struct A
{
    A &operator=(int (a[10]))
    {
        for (int i=0; i<10; i++)
            cout << a[i];

        return *this;
    }
};


int main()
{
    int x[10] = {1,2,3,4,5,6,7,8,9,0};

    A a;
    a = x;
}