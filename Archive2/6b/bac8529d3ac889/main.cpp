#include <iostream>
#include <cstdlib>
#include <malloc.h>

using namespace std;

struct A
{ 
    void* operator new[] (size_t t, int)
    {
        cout << "Member allocation" << endl;
        return malloc(t);
    }
    
    void operator delete [](void *p, size_t t)
    {
        cout << "Deallocation" << endl;
        ::operator delete [](p, t);
    }
};

int main()
{
    A *p = new (5) A[10];
    delete [] p;
}