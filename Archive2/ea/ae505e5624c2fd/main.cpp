#include <iostream>

struct A {
    A(void *) {}
    A() {}
};

class B : public A {
public:
    using A::A;
    B(int x) {}
};

int main()
{
    B b(4);
}