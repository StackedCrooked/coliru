#include <iostream>
#include <new>
#include <cstdlib>

using std::cout;

struct C{ };

struct A
{
    void* operator new(std::size_t, C*){ A a; return &a; }
};

C c;

A *a= new (&c, &c) A;

int main(){ }