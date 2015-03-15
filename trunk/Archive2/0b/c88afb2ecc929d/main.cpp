#include<iostream>

using namespace std;

class A
{
public:
    virtual void foo(){ std::cout << "foo" << std::endl; }
};

class B : public A
{
public:
    void foo(){ std::cout << "overriden foo" << std::endl; }
};

A c = B();

int main(){ c.foo(); }