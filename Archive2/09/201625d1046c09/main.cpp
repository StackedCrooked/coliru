#include <iostream>
#include <cstdlib>
#include <malloc.h>

using namespace std;

void* operator new[](size_t t, size_t)
{
    cout << "allocation" << endl;
    return malloc(t);
}

void operator delete[](void *p, size_t t)
{
    cout << "deallocation" << endl;
    free(p);
}

struct A{ };

int main()
{
    A *a = new (90) A[5];
    operator delete[](a, 5);
}