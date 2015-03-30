#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <type_traits>
#include <functional>
#include <typeinfo>
#include <memory>

struct A
{
    virtual void f() const { std::cout << "A\n"; }
};

struct B : public A
{
    void f() const { std::cout << "B\n"; }
};

void test(const A& a)
{
    a.f();
}

void g(const A* a)
{
    test(*a);
}

int main()
{
    std::vector<A*> aa;
    for(int t = 0; t < 20; t++)
        aa.push_back(std::rand() % 2 == 0 ? new A() : new B());
    for(int t = 0; t < 20; t++)
    {
        std::cout << t << " : ";
        g(aa[t]);
    }
}
