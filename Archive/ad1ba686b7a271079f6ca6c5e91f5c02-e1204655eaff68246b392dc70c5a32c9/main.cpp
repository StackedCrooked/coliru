#include <iostream>

struct B
{
};

struct A : B
{
    operator A* ();
    operator B* ();
};


int main() {
    A a;
    void* x = a;
    (void)x;
}
