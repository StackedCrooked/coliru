#include <iostream>
#include <cstdlib>

using namespace std;

struct A
{ 
    void operator delete[](void *p)
    {
        cout << "delete\n";
        ::operator delete[](p);
    }
    void operator delete[](void *p, size_t t)
    {
        cout << "delete with two arguments\n";
        ::operator delete[](p);
    }
};

int main()
{
    A *a = new A[5];
    delete [] a;
}