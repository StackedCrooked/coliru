#include <iostream>
#include <cstdlib>

using std::cout;
using namespace std;

struct A
{ 
    int a;
    A(){ cout << "Constructor\n"; a = 4; } 
    void * operator new[](size_t t)
    {
        cout << "new!\n";
        return ::operator new(t); //Non-array memory allocation!
    }
};

int main()
{
    A *a = new A[5];
    cout << a <<"\n";
    for(int i = 0; i < 5; i++)
    {
        cout << a[i].a;
    }
}