#include <iostream>
#include <functional>

struct T{};

struct A
{
    virtual void foo(int, T*) = 0;
    virtual void foo1(int, T*) = 0;
    virtual ~A() = default;
};

struct B : A
{
    void foo(int, T*) override {std::cout << __PRETTY_FUNCTION__ << std::endl;}
    void foo1(int, T*) override {std::cout << __PRETTY_FUNCTION__ << std::endl;}
};

struct D
{
    void client_foo(A* pA, bool b, T* pT)
    {
        if (b) client_helper(pA, 1050, pT, &A::foo);
        else client_helper(pA, 5010, pT, &A::foo1);
    }

    void client_helper(A* pA, int i, T* pT, void(A::*memfn)(int, T*))
    {
        (pA->*memfn)(i, pT);
    }
};

int main()
{
    B b;
    T t;
    D d;

    d.client_foo(&b, true, &t);
    d.client_foo(&b, false, &t);
}
