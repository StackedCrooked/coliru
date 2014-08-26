#include <stdio.h>

class A:
{
    A(){}
    ~A(){}

    void methodX() {
        printf ("I am class A implementation");
    }

    void methodZ()
    {
        methodX();
    }
};

class B: public A
{
    B(){}
    ~B(){}

    void methodX() {
        printf ("I am class B implementation");
    }

    void methodZ() {
        A::methodZ();
        methodX();
    }
};

B *b = new B();
b->methodZ();

A *a = new B();
a->methodZ();