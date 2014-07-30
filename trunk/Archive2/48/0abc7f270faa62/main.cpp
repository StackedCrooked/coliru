#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

struct A
{
    void * operator new(size_t t, size_t) 
    {
        cout << "Allocation" << endl;
        return ::operator new(t);
    }

    void operator delete (void *p, size_t t)
    {
        cout << "Delete" << endl;
        ::operator delete (p, t);
    }
};

A a;

int main()
{
    delete &a;
}
