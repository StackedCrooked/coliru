#include <stdio.h>

class A {
public:
    A(){}
    ~A(){}

    void methodX() {
        printf ("I am class A implementation\n");
    }

    void methodZ()
    {
        methodX();
    }
};

class B: public A
{
public:
    B(){}
    ~B(){}

    void methodX() {
        printf ("I am class B implementation\n");
    }

    void methodZ() {
        A::methodZ();
        methodX();
    }
};

int main() {
  B *b = new B();
  b->methodZ();

  A *a = new B();
  a->methodZ();
}