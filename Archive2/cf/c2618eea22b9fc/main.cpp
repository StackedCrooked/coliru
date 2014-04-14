#include <iostream>
#include <algorithm>
#include <set>

struct B
{
    virtual void f() {}
};

struct D : B
{
    virtual void f() {}
};

struct S1
{
    virtual void s(B&){std::cout << "bbbb"; }
};

struct SS
{
    virtual void s(D&){std::cout << "dddd"; }
}

struct S2 : S1, SS
{
    virtual void s(D&){std::cout << "dddd"; }
};

int main()
{
    D d;
    S2 s2;
    s2.s(d);
}