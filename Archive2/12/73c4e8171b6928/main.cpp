#include <iostream>
#include <cstdlib>
#include <malloc.h>

using namespace std;

void* operator new[](size_t t, size_t)
{
    cout << "allocation" << endl;
    return malloc(t);
}

struct A
{ 
    void* operator new[](size_t t, size_t)
    {
        cout << "Member allocation" << endl;
        return malloc(t);
    }

    void operator delete[](void *p) noexcept
    {
        cout << "one argument dealloaction" << endl;
    }
    
    void operator delete[](void *p, size_t t)
    {
        cout << "two arguments deallocation" << endl;
        free(p);
    }
};

int main()
{
    int n =5;
    float ** p = new float[n][5];
}