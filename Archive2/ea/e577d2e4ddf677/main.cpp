#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>
#include <functional>
#include <memory>

using namespace std;

struct Alloc1 {
    static void *operator new (size_t sz)    { cout << "op-new 1: " << sz <<  endl; return malloc(sz); }
    static void operator delete (void *ptr)  { cout << "op-del 1" <<  endl; return free(ptr);  }
};

struct Alloc2 {
    static void *operator new (size_t sz)    { cout << "op-new 2: " << sz <<  endl; return malloc(sz); }
    static void operator delete (void *ptr)  { cout << "op-del 2" <<  endl; return free(ptr);  }
};

struct A : Alloc1
{
    int x;
    A() { cout << "A" << endl; }
    ~A() { cout << "~A" << endl; } 
};

struct B : A , Alloc2
{
    static void *operator new (size_t sz)    { cout << "op-new 3: " << sz <<  endl; return malloc(sz); }
    static void operator delete (void *ptr)  { cout << "op-del 3" <<  endl; return free(ptr);  }
    
    int y;
    B() { cout << "B" << endl; }
    ~B() { cout << "~B" << endl; } 
};

int main()
{
    shared_ptr<A> a(new B);
}


