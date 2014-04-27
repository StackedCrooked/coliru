#include <cstdio>

struct Base;

struct BaseVTableLayout {
    int (*virtualCall)(Base*);
};

struct Base { BaseVTableLayout const* vptr; };
struct Derived: Base {};

int Derived_virtualCall(Base*) { return 42; }

BaseVTableLayout const BaseVTable = { 0 };
BaseVTableLayout const DerivedVTable = { &Derived_virtualCall };

void opaque(Base*);

int add(Base** array, size_t size) {
    int total = 0;
    for (size_t i = 0; i != size; ++i) {
        Base* b = array[i];
        
        opaque(b);
        
        total += b->vptr->virtualCall(b);
    }
    return total;
}

int func() {
    Derived d0;
    d0.vptr = &DerivedVTable;
    Derived d1;
    d1.vptr = &DerivedVTable;
    Derived d2;
    d2.vptr = &DerivedVTable;
    
    Base* b[3] = { &d0, &d1, &d2 };

    return add(b, 3);
}