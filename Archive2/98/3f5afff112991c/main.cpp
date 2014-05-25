#include <stdio.h>
#include <stdlib.h>

struct X
{
  X() { puts("X()"); }
  X(const X &) { puts("X(const X &)"); }
  X(int) { puts("X(int)"); }
};

X foo()
{
    puts("foo()");
    X x(0);
    X y(1);
    X z;
    if (rand() > 50)
        z = x;
    else
        z = y;
    return z;
}

X bar()
{
    puts("bar()");
    X x(0);
    X y(1);
    if (rand() > 50)
        return x;
    else
        return y;
}

X z1 = foo();
X z2 = bar();

int main() { }