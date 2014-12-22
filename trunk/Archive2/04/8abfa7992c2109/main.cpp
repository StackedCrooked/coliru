#include <iostream>

struct X 
{ 
    virtual void foo() { std::cout << "X"; } 
};

struct Y : X 
{ 
    virtual void foo() override { std::cout << "Y"; } 
};

X x;
Y y;

struct A
{
    virtual X* bar() { return &x; }
};

struct B : A
{
    virtual Y* bar() override { return &y; }
};

int main()
{
    B b;    
    A& a = b;
    a.bar()->foo();    
}