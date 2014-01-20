#include <iostream>
#include <list>

struct A
{
    virtual void hello()
       { std::cout << "Hello from A\n"; }
};

struct B : public A
{
    virtual void hello()
       { std::cout << "Hello from B\n"; }
};

int main()
{
    std::list<A>  l1;
    std::list<A*> l2;
    A a;
    B b;

    l1.push_back(a);
    l1.push_back(b);

    l2.push_back(&a);
    l2.push_back(&b);

    l1.front().hello();
    l1.back().hello();

    l2.front()->hello();
    l2.back()->hello();
}