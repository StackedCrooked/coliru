#include <cstdio>

struct Base;

struct BaseVTableLayout {
    void (*virtualCall)(Base*);
};

struct Base { BaseVTableLayout const* vptr; };
struct Derived: Base {};

void Derived_virtualCall(Base*) { printf("Hello, World!\n"); }

BaseVTableLayout const BaseVTable = { 0 };
BaseVTableLayout const DerivedVTable = { &Derived_virtualCall };

void inlinable(Base* b) { b->vptr->virtualCall(b); }

void opaque(Base* b);

void funky(Base* b) {
    BaseVTableLayout const* vptr = b->vptr;
    inlinable(b); // statement A
    b->vptr = vptr; // inform LLVM that the function is not allowed to change the virtual pointer under our feet

    opaque(b); // Unknown implementation, LLVM assumes it may change the virtual pointer
    b->vptr = vptr; // inform LLVM that the function is not allowed to change the virtual pointer under our feet

    inlinable(b); // statement B
    b->vptr = vptr; // inform LLVM that the function is not allowed to change the virtual pointer under our feet
}

void func() {
    Derived d;
    d.vptr = &DerivedVTable;

    funky(&d);
}