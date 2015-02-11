#include<cstdio>

struct A {
    void f() { } ;
    void g() const { f(); }
};

int main()
{
    A a ;
    a.g();
}