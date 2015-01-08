#include <iostream>

struct A 
{ 
    int d; 
    A(int d) : d(d) {}
}; 

struct B
{
    A *_m; 
    B(A *m) : _m(_m) {}
};


int main()
{
    A *a = new A(2); 
    B obj(a);
    delete a; 
}