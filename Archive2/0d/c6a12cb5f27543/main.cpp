#include <cstdio>

struct Base { virtual void virtualCall() = 0; };
struct Derived: Base { virtual void virtualCall() override { printf("Hello, World!\n"); } };

void inlinable(Base& b) { b.virtualCall(); }
void opaque(Base& b);

void func() {
    Derived d;

    inlinable(d); // statement A
    opaque(d); // Unknown implementation, LLVM assumes it may change the virtual pointer

    inlinable(d); // statement B
}