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

void func() {
    Derived d;
    d.vptr = &DerivedVTable;

    inlinable(&d); // statement A
    d.vptr = &DerivedVTable; // inform LLVM that the function is not allowed to change the virtual pointer under our feet

    opaque(&d); // Unknown implementation, LLVM assumes it may change the virtual pointer
    d.vptr = &DerivedVTable; // inform LLVM that the function is not allowed to change the virtual pointer under our feet

    inlinable(&d); // statement B
    d.vptr = &DerivedVTable; // inform LLVM that the function is not allowed to change the virtual pointer under our feet
}