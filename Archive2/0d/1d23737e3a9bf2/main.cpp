#include <iostream>

struct base0
{
    int m = 42;
    ~base0() { std::cout << "base0 "<<m<<"\n"; }
};

struct base1
{
    int m = 21;
    ~base1() { std::cout << "base1 "<<m<<"\n"; }
};

struct derived : base0, base1
{
    int m = 12;
    ~derived() { std::cout << "derived "<<m<<"\n"; }
};

void deleter(void* p)
{
    static_cast<derived*>(p)->~derived();
}

int main()
{
    base0* p0 = new derived;
    deleter(p0);
    
    base1* p1 = new derived;
    deleter(p1);
}