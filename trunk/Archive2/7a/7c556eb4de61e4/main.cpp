#include <iostream>

struct B
{
    void foo(int a){ }  
};

struct C
{
    void foo(int a){ }
};

struct A : B, C
{
};

A a;



int main(){ a.foo(3); }