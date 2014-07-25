#include <iostream>
#include <cstdlib>

using namespace std;

struct A
{
    void* operator new[](size_t t, size_t t2)
    {
        cout << "allocation" << ' ' << t << ' ' << t2<< endl;
        return ::operator new[](t);
    }
    
    void operator delete[](void *p, size_t t)
    {
        cout << "deallocation" << ' '  << t << endl;
        :: operator delete[](p);
    }
};

int main()
{
    A *a = new (90) A[5];
    delete [] a;
}