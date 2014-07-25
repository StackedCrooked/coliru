#include <iostream>
#include <cstdlib>

using namespace std;

struct A
{
    void* operator new[](size_t t, size_t)
    {
        cout << "allocation" << endl;
        return ::operator new[](t);
    }
    
    void operator delete[](void *p)
    {
        cout << "deallocation - usual" << endl;
        :: operator delete[](p);
    }
    void operator delete[](void *p, size_t t)
    {
        cout << "deallocation - placement" << endl;
        :: operator delete[](p);
    }
};

int main()
{
    A *a = new (90) A[5];
    delete [] a;
}